import RPi.GPIO as GPIO
import time
import base64
import urllib
import requests
import json
import subprocess
import os
import websocket
import datetime
import hashlib
import hmac
from urllib.parse import urlencode
import ssl
from wsgiref.handlers import format_date_time
from datetime import datetime
from time import mktime
import _thread as thread

# 设置你的API密钥
API_KEY = "vCh01RKSh9MgPFmNxk1KTgMs"
SECRET_KEY = "TvhOl1xXwbt9ufoOcDoihp2zEXwsKZmH"
GPT_API_KEY = 'sk-F0mw1gRTj8KbcSChiYoDpgca8G4kjX6wgJCmgmFzGKA70g3s'  # 替换为你的ChatGPT API密钥
TTS_APPID = 'f6050d06'
TTS_APIKey = '35a481a85a2c6e53f4469a6835c3d101'
TTS_APISecret = 'YWZmODZjYjUzOTRkNWE0MGM0ZmQ5YjQz'

# 设置GPIO模式
GPIO.setmode(GPIO.BCM)  # 使用 BCM 模式
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # 设置 GPIO 21 为输入，内部上拉电阻

def record_audio(filename, duration):
    command = [
        "arecord",
        "-D", "plughw:2,0",  # 使用你的音频设备
        "-f", "S16_LE",      # 音频格式
        "-c", "1",           # 通道数
        "-r", "8000",        # 采样率
        filename
    ]
    
    process = subprocess.Popen(command)
    try:
        print(f"Recording for {duration} seconds...")
        process.wait(timeout=duration)
    except subprocess.TimeoutExpired:
        print("Recording stopped due to timeout.")
        process.terminate()

def get_file_content_as_base64(path, urlencoded=False):
    with open(path, "rb") as f:
        content = base64.b64encode(f.read()).decode("utf8")
        if urlencoded:
            content = urllib.parse.quote_plus(content)
    return content

def get_access_token():
    url = "https://aip.baidubce.com/oauth/2.0/token"
    params = {"grant_type": "client_credentials", "client_id": API_KEY, "client_secret": SECRET_KEY}
    return str(requests.post(url, params=params).json().get("access_token"))

def recognize_speech(filename):
    url = "https://vop.baidubce.com/server_api"
    
    speech = get_file_content_as_base64(filename)
    payload = json.dumps({
        "format": "pcm",
        "rate": 8000,
        "channel": 1,
        "cuid": "iJ5MXG7amA9WAqhlduRHr7o2kHzAynXC",
        "speech": speech,
        "len": os.path.getsize(filename),
        "token": get_access_token()
    })
    
    headers = {
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    }
    
    response = requests.post(url, headers=headers, data=payload)
    
    print("Recognition Result:")
    result_json = response.json()
    
    # 提取具体的识别结果
    if result_json.get("err_no") == 0:
        recognized_text = result_json.get("result")[0]  # 获取第一个识别结果
        print(f"识别出的内容: {recognized_text}")
        return recognized_text
    else:
        print(f"错误信息: {result_json.get('err_msg')}")
        return None

def send_prompt(prompt=''):
    if not prompt:
        print("Prompt is empty")
        return
    
    headers = {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + GPT_API_KEY
    }
    
    data = {
        "model": "gpt-3.5-turbo",
        "messages": [
            {"role": "system", "content": "You are a helpful assistant."},
            {"role": "user", "content": prompt}
        ]
    }
    
    try:
        response = requests.post('https://api.001hao.com/v1/chat/completions', headers=headers, data=json.dumps(data))
        response.raise_for_status()  # 检测请求是否成功
        response_data = response.json()
        
        if response_data.get('choices'):
            response_text = response_data['choices'][0].get('message', {}).get('content', '')
            print("ChatGPT回复:", response_text)
            return response_text
    except requests.exceptions.RequestException as e:
        print("请求错误:", e)

class Ws_Param(object):
    def __init__(self, APPID, APIKey, APISecret, Text):
        self.APPID = APPID
        self.APIKey = APIKey
        self.APISecret = APISecret
        self.Text = Text
        self.CommonArgs = {"app_id": self.APPID}
        self.BusinessArgs = {"aue": "raw", "auf": "audio/L16;rate=16000", "vcn": "xiaoyan", "tte": "utf8"}
        self.Data = {"status": 2, "text": str(base64.b64encode(self.Text.encode('utf-8')), "UTF8")}

    def create_url(self):
        url = 'wss://tts-api.xfyun.cn/v2/tts'
        now = datetime.now()
        date = format_date_time(mktime(now.timetuple()))
        signature_origin = "host: " + "ws-api.xfyun.cn" + "\n"
        signature_origin += "date: " + date + "\n"
        signature_origin += "GET " + "/v2/tts " + "HTTP/1.1"
        signature_sha = hmac.new(self.APISecret.encode('utf-8'), signature_origin.encode('utf-8'),
                                 digestmod=hashlib.sha256).digest()
        signature_sha = base64.b64encode(signature_sha).decode(encoding='utf-8')
        authorization_origin = "api_key=\"%s\", algorithm=\"%s\", headers=\"%s\", signature=\"%s\"" % (
            self.APIKey, "hmac-sha256", "host date request-line", signature_sha)
        authorization = base64.b64encode(authorization_origin.encode('utf-8')).decode(encoding='utf-8')
        v = {
            "authorization": authorization,
            "date": date,
            "host": "ws-api.xfyun.cn"
        }
        url = url + '?' + urlencode(v)
        return url

def on_message(ws, message):
    try:
        message = json.loads(message)
        code = message["code"]
        audio = message.get("data", {}).get("audio")
        if audio:
            audio = base64.b64decode(audio)
            with open('./response.pcm', 'ab') as f:
                f.write(audio)
        status = message.get("data", {}).get("status")
        if status == 2:
            print("ws is closed")
            ws.close()
            play_audio('response.pcm')
    except Exception as e:
        print("receive msg, but parse exception:", e)

def on_error(ws, error):
    print("### error:", error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    def run(*args):
        d = {"common": wsParam.CommonArgs,
             "business": wsParam.BusinessArgs,
             "data": wsParam.Data,
             }
        d = json.dumps(d)
        print("------>开始发送文本数据")
        ws.send(d)
        if os.path.exists('./response.pcm'):
            os.remove('./response.pcm')

    thread.start_new_thread(run, ())

def text_to_speech(text, appid, apikey, apisecret):
    global wsParam
    wsParam = Ws_Param(APPID=appid, APIKey=apikey, APISecret=apisecret, Text=text)
    wsUrl = wsParam.create_url()
    ws = websocket.WebSocketApp(wsUrl, on_message=on_message, on_error=on_error, on_close=on_close)
    ws.on_open = on_open
    ws.run_forever(sslopt={"cert_reqs": ssl.CERT_NONE})

def play_audio(filename):
    # 使用aplay播放音频，并指定采样率为16000Hz
    command = ["aplay", "-r", "16000", "-c", "1", "-f", "S16_LE", filename]
    process = subprocess.Popen(command)
    process.communicate()

def main():
    output_file = "output.pcm"
    record_duration = 10  # 录制10秒钟

    try:
        while True:
            # 检查GPIO电平状态
            status = GPIO.input(21)
            print("GPIO状态:", status)  # 1 为高电平，0 为低电平
            
            if status == 0:  # 当GPIO状态为0时开始录音
                print("检测到低电平，开始录音...")
                record_audio(output_file, record_duration)
                recognized_text = recognize_speech(output_file)
                os.remove(output_file)  # 删除录音文件
                
                # 如果识别成功，发送给ChatGPT
                if recognized_text:
                    gpt_response = send_prompt(recognized_text)
                    if gpt_response:
                        text_to_speech(gpt_response, TTS_APPID, TTS_APIKey, TTS_APISecret)

            time.sleep(1)  # 等待1秒钟再检查

    except KeyboardInterrupt:
        print("程序结束")
    finally:
        GPIO.cleanup()  # 清理GPIO设置

if __name__ == '__main__':
    main()