import re
import random
import os


def clean_text(text):
    # 去除非中文字符、英文字符和标点符号的其他字符
    text = re.sub(r'[^\w\u4e00-\u9fff，。、！？；：“”‘’（）《》【】\s]', '', text)
    # 将英文标点替换为中文标点，其他标点替换为逗号
    text = text.replace(',', '，').replace('.', '。').replace('!', '，').replace('?', '，').replace('!', '，').replace(';','，').replace(':', '，')
    return text


def split_sentences(text):
    sentences = re.split(r'[，。]', text)
    new_sentences = []
    for index, sentence in enumerate(sentences):
        parts = sentence.split('，')
        combined_sentence = ""
        for part in parts:
            if len(part.strip()) < 5:
                combined_sentence += part
            else:
                if combined_sentence:
                    combined_sentence += " " + part
                else:
                    combined_sentence = part
        combined_sentence = combined_sentence.strip()
        if combined_sentence:
            # 给英文单词前后添加空格
            combined_sentence = re.sub(r'([a-zA-Z]+)([\u4e00-\u9fff])', r'\1 \2', combined_sentence)
            combined_sentence = re.sub(r'([\u4e00-\u9fff])([a-zA-Z]+)', r'\1 \2', combined_sentence)
            # 清除句子开头和结尾除句号外的标点符号
            combined_sentence = re.sub(r'^[，、！？；：“”‘’（）《》【】]*([^。，、！？；：“”‘’（）《》【】]*)[，、！？；：“”‘’（）《》【】]*$', r'\1',
                                       combined_sentence)
            new_sentences.append(combined_sentence)
    return new_sentences


def save_sentences(sentences):
    output_dir = r"D:\output"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    for index, sentence in enumerate(sentences, start=1):
        file_path = os.path.join(output_dir, f"{index}.txt")
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(sentence)


def rearrange_sentences(sentences):
    random.seed(20221492506)
    random_num = [random.randint(1, len(sentences)) for _ in range(10)]
    new_order = []
    for num in random_num:
        new_order.append(sentences[num - 1])
    return new_order


if __name__ == "__main__":
    input_file_path = r"D:\input.txt"
    with open(input_file_path, 'r', encoding='utf-8') as f:
        text = f.read()
    cleaned_text = clean_text(text)
    sentences = split_sentences(cleaned_text)
    save_sentences(sentences)
    rearranged_sentences = rearrange_sentences(sentences)
    save_sentences(rearranged_sentences)
