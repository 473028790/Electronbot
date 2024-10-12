from PIL import Image
import numpy as np
import serial
import time

def convert_to_18bit_true_color(image_path):
    # 打开图像并将其转换为RGB格式
    image = Image.open(image_path).convert('RGB')

    # 获取图像的尺寸
    width, height = image.size

    # 获取像素数据
    pixels = np.array(image)

    # 初始化用于存储18位真彩色数据的字节数组
    byte_array = np.zeros((height, width, 3), dtype=np.uint8)

    # 遍历每个像素并转换为18位真彩色格式
    for y in range(height):
        for x in range(width):
            r, g, b = pixels[y, x]

            # 将RGB值转换为6位（18位真彩色）
            r_6bit = (r >> 2) & 0x3F  # 取高6位
            g_6bit = (g >> 2) & 0x3F  # 取高6位
            b_6bit = (b >> 2) & 0x3F  # 取高6位

            # 将6位颜色值扩展为8位，并存储在数组中
            byte_array[y, x, 0] = r_6bit << 2
            byte_array[y, x, 1] = g_6bit << 2
            byte_array[y, x, 2] = b_6bit << 2

    # 展平数组为1D数组
    byte_array = byte_array.flatten()

    return byte_array, width, height

def export_to_c_array(byte_array, output_path):
    # 将 byte_array 拆分为 4 个部分
    quarter_size = len(byte_array) // 4
    parts = [byte_array[i * quarter_size:(i + 1) * quarter_size] for i in range(4)]

    # 创建C数组的字符串表示
    c_array_str = "const uint8_t gImage_2[4][43200] = {\n"

    for part in parts:
        c_array_str += "    {"
        for i, byte in enumerate(part):
            if i % 16 == 0:  # 每行16个字节
                c_array_str += "\n        "
            c_array_str += f"0x{byte:02X}, "
        c_array_str = c_array_str.rstrip(", ")  # 去掉最后一个逗号和空格
        c_array_str += "\n    },\n"

    c_array_str = c_array_str.rstrip(",\n") + "\n};\n"  # 去掉最后的逗号并加上结尾的分号

    # 导出到txt文件
    with open(output_path, "w") as f:
        f.write(c_array_str)

    print(f"C数组成功导出到 {output_path}")

def send_byte_array_over_serial(byte_array, port, baudrate=115200):
    try:
        # 打开串口
        ser = serial.Serial(port, baudrate, timeout=1)

        # 计算1/4的大小
        quarter_size = len(byte_array) // 4

        first_chunk = None  # 用于保存第一次发送的数据
        last_chunk = None   # 用于保存最后发送的数据

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

            # 保存第一次发送的512个数据
            #if part == 0:
            #    first_chunk = total_data[:512]  # 记录第一次发送的512个字节

            # 保存最后发送的224个字节
            #if part == 3:
            #    last_chunk = total_data[-224:]  # 记录最后发送的224个字节

            # 发送数据
            ser.write(total_data)
            print(f"发送数据包，共 {len(total_data)} 字节")
            time.sleep(0.02)

        # 关闭串口
        ser.close()
        print("所有数据已发送完毕")

        # 打印第一次和最后一次发送的数据
        #if first_chunk is not None:
        #    print("第一次发送的512个字节:", [f"0x{byte:02X}" for byte in first_chunk])
        #if last_chunk is not None:
        #    print("最后发送的224个字节:", [f"0x{byte:02X}" for byte in last_chunk])

    except serial.SerialException as e:
        print(f"无法打开串口 {port}: {e}")

# 图片路径
#image_path = r'C:\Users\47302\Desktop\20240811161222.jpg'
image_path = r'C:\Users\47302\Desktop\6.jpg'
# 输出路径
output_path = r'C:\Users\47302\Desktop\gImage_2.txt'
# 串口配置
port = 'COM25'
baudrate = 115200  # 可以根据需要设置

# 转换为18位真彩色并获取byte_array
byte_array, width, height = convert_to_18bit_true_color(image_path)

# 导出为C数组格式的txt文件
export_to_c_array(byte_array, output_path)

# 通过串口发送byte_array
start_time = time.time()
send_byte_array_over_serial(byte_array, port, baudrate)
end_time = time.time()

# 计算并打印总耗时
total_time = end_time - start_time
print(f"数据传输完成，耗时: {total_time:.4f} 秒")
