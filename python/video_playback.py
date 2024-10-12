import cv2
from PIL import Image
import numpy as np
import serial
import time

# 保留之前的 convert_to_18bit_true_color 和 send_byte_array_over_serial 函数
def convert_to_18bit_true_color(image):
    image = Image.fromarray(image).convert('RGB')  # 从帧数据转换为RGB格式
    width, height = image.size
    pixels = np.array(image)

    byte_array = np.zeros((height, width, 3), dtype=np.uint8)

    for y in range(height):
        for x in range(width):
            r, g, b = pixels[y, x]
            r_6bit = (r >> 2) & 0x3F
            g_6bit = (g >> 2) & 0x3F
            b_6bit = (b >> 2) & 0x3F
            byte_array[y, x, 0] = r_6bit << 2
            byte_array[y, x, 1] = g_6bit << 2
            byte_array[y, x, 2] = b_6bit << 2

    return byte_array.flatten(), width, height

def send_byte_array_over_serial(byte_array, port, baudrate=115200):
    try:
        # 打开串口
        ser = serial.Serial(port, baudrate, timeout=1)

        # 计算1/4的大小
        quarter_size = len(byte_array) // 4

        for part in range(4):
            # 每次发送1/4的数据
            start_index = part * quarter_size
            end_index = start_index + quarter_size if part < 3 else len(byte_array)
            chunk = byte_array[start_index:end_index]

            # 计算需要发送的数据大小
            total_data = bytearray()

            if len(chunk) % 512 != 0:  # 如果不能被512整除
                remaining_bytes = chunk  # 使用当前chunk
                total_data.extend(remaining_bytes)  # 添加剩余的字节
                total_data.extend(bytes([0x00] * 32))  # 添加32字节的调试数据
                print(f"添加了 {len(remaining_bytes)} 字节和32字节的调试数据，总共发送 {len(total_data)} 字节")
            else:
                # 分批发送512个字节的数据
                packet_size = 512
                bytes_sent = 0

                while bytes_sent < len(chunk):
                    packet = chunk[bytes_sent:bytes_sent + packet_size]
                    total_data.extend(packet)  # 直接添加到总数据
                    bytes_sent += len(packet)
                    print(f"已发送 {len(packet)} 字节，共发送 {bytes_sent}/{len(chunk)} 字节")

                # 如果发送完当前部分，没有剩余
                if bytes_sent == len(chunk):
                    total_data.extend(bytes([0x00] * 32))  # 添加32字节的调试数据
                    print("添加了32字节的调试数据")

            # 发送数据
            ser.write(total_data)
            print(f"发送数据包，共 {len(total_data)} 字节")
            time.sleep(0.05)

        # 关闭串口
        ser.close()
        print("所有数据已发送完毕")

    except serial.SerialException as e:
        print(f"无法打开串口 {port}: {e}")

def process_video_and_store_frames(video_path, frame_skip=5):
    # 打开视频文件
    video_capture = cv2.VideoCapture(video_path)

    if not video_capture.isOpened():
        print(f"无法打开视频文件 {video_path}")
        return []

    frame_count = 0
    processed_frames = 0
    all_frames = []

    while True:
        ret, frame = video_capture.read()  # 读取一帧
        if not ret:
            print("视频读取结束")
            break

        frame_count += 1

        # 每隔 frame_skip 帧处理一次
        if frame_count % frame_skip == 0:
            processed_frames += 1
            print(f"处理第 {frame_count} 帧 (抽帧), 这是第 {processed_frames} 个处理的帧...")

            # 将帧转换为18位真彩色并获取字节数组
            byte_array, width, height = convert_to_18bit_true_color(frame)

            # 存储帧的字节数组
            all_frames.append(byte_array)

    print(f"视频处理完成，总帧数: {frame_count}, 处理帧数: {processed_frames}")

    # 释放视频捕获对象
    video_capture.release()

    return all_frames

def send_frames_over_serial(all_frames, port, baudrate=115200):
    # 逐帧发送已处理的帧
    for i, frame_data in enumerate(all_frames):
        print(f"发送第 {i+1} 帧，共 {len(frame_data)} 字节")
        send_byte_array_over_serial(frame_data, port, baudrate)

# 视频路径
video_path = r'C:\Users\47302\Desktop\666.mp4'
# 串口配置
port = 'COM25'
baudrate = 115200  # 可以根据需要设置

# 设置抽帧间隔（例如每隔5帧处理1帧）
frame_skip = 2

# 第一步：处理视频，存储所有帧的字节数组
all_frames = process_video_and_store_frames(video_path, frame_skip)

# 第二步：通过串口逐帧发送所有已处理的帧
if all_frames:
    send_frames_over_serial(all_frames, port, baudrate)
