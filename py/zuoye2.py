import wave
import numpy as np
import matplotlib.pyplot as plt
import pyaudio  # 如果需要录制音频则导入

# 音频录制函数（如果需要录制音频）
def record_audio(file_name, duration, sample_rate):
    p = pyaudio.PyAudio()
    stream = p.open(format=pyaudio.paInt16,
                    channels=1,
                    rate=sample_rate,
                    input=True,
                    frames_per_buffer=1024)
    print("开始录制音频...")
    frames = []
    for i in range(0, int(sample_rate / 1024 * duration)):
        data = stream.read(1024)
        frames.append(data)
    print("音频录制完成。")
    stream.stop_stream()
    stream.close()
    p.terminate()
    wf = wave.open(file_name, 'wb')
    wf.setnchannels(1)
    wf.setsampwidth(p.get_sample_size(pyaudio.paInt16))
    wf.setframerate(sample_rate)
    wf.writeframes(b''.join(frames))
    wf.close()

# 读取音频文件并预处理
def read_and_preprocess_audio(file_name):
    wf = wave.open(file_name, 'rb')
    sample_rate = wf.getframerate()
    n_channels = wf.getnchannels()
    n_frames = wf.getnframes()
    audio_data = wf.readframes(n_frames)
    wf.close()
    audio_data = np.frombuffer(audio_data, dtype=np.int16)
    # 这里可以添加去除前后无音区的代码
    return audio_data, sample_rate

# 分帧函数
def frame_audio(audio_data, frame_length):
    frames = []
    for i in range(0, len(audio_data) - frame_length + 1, frame_length):
        frames.append(audio_data[i:i + frame_length])
    return frames

# 傅里叶变换函数
def fourier_transform(frame):
    return np.fft.fft(frame)

# 找到频谱幅度最大的频率点
def find_max_frequencies(spectrum, num_points):
    magnitudes = np.abs(spectrum)
    max_indices = np.argsort(magnitudes)[-num_points:]
    return max_indices

# 信息嵌入函数
def embed_information(spectrum, unicode_value):
    unicode_digits = [int(digit) for digit in hex(unicode_value)[2:]]
    max_indices = find_max_frequencies(spectrum, len(unicode_digits))
    for i, index in enumerate(max_indices):
        spectrum[index] += unicode_digits[i]
    return spectrum

# 傅里叶逆变换函数
def inverse_fourier_transform(spectrum):
    return np.fft.ifft(spectrum)

# 重组语音信号
def reconstruct_audio(frames):
    return np.concatenate(frames)

# 绘制波形图函数
def plot_waveform(audio_data, sample_rate, title):
    time = np.arange(0, len(audio_data)) / sample_rate
    plt.plot(time, audio_data)
    plt.xlabel('时间 (秒)')
    plt.ylabel('幅度')
    plt.title(title)
    plt.show()

# 绘制频谱图函数
def plot_spectrum(spectrum, sample_rate, title):
    frequencies = np.fft.fftfreq(len(spectrum), 1 / sample_rate)
    magnitudes = np.abs(spectrum)
    plt.plot(frequencies, magnitudes)
    plt.xlabel('频率 (Hz)')
    plt.ylabel('幅度')
    plt.title(title)
    plt.show()

if __name__ == "__main__":
    # 录制音频（如果需要录制）
    # record_audio('your_student_id.wav', duration=5, sample_rate=16000)

    # 读取并预处理音频
    audio_data, sample_rate = read_and_preprocess_audio('your_student_id.wav')

    # 分帧
    frames = frame_audio(audio_data, frame_length=2048)

    # 对第5帧进行傅里叶变换
    spectrum = fourier_transform(frames[4])

    # 绘制原始频谱图
    plot_spectrum(spectrum, sample_rate, '原始频谱图')

    # 信息嵌入
    unicode_value = 27743  # “辽”字的十六进制unicode编码值
    new_spectrum = embed_information(spectrum.copy(), unicode_value)

    # 绘制嵌入信息后的频谱图
    plot_spectrum(new_spectrum, sample_rate, '嵌入信息后的频谱图')

    # 傅里叶逆变换
    new_frame = inverse_fourier_transform(new_spectrum)

    # 替换第5帧
    frames[4] = new_frame.real.astype(np.int16)

    # 重组语音信号
    new_audio_data = reconstruct_audio(frames)

    # 绘制嵌入信息后的波形图
    plot_waveform(new_audio_data, sample_rate, '嵌入信息后的波形图')

    # 对比原始和嵌入信息后的波形图（这里可进一步进行客观数据比对分析）
    plot_waveform(audio_data, sample_rate, '原始波形图')

    # 信息提取探讨（这里需要进一步完善提取算法）