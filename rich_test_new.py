import os
import time
import filecmp
import subprocess
import json
from collections import OrderedDict

process = None
# b'step5\r\nN\r\nquit\r\n'
# b'Step 5\r\nN\r\nquit\r\n'
def run_exe_with_input(exe_path, input_file, json_file):
    try:
        print(f"Running {exe_path} with arguments {json_file} and {input_file}")
        with subprocess.Popen([exe_path, json_file], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True) as process:
            print(f"Running {exe_path} with input file {input_file}")
            input_data = open(input_file, 'rb').read() + b"\r\nQuit"
            print(input_data)
            output, _ = process.communicate(input=input_data, timeout=10)   # 读取输出并等待进程完成，设置超时时间为10秒
            print(output.decode('utf-8'))
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        if process:
            process.terminate()

def compare_outputs(test_folder):
    total_files = 0
    successful_tests = 0
    failed_tests = []  # 添加一个列表来存储失败的测试用例名称

    for folder in os.listdir(test_folder):
        if os.path.isdir(os.path.join(test_folder, folder)):
            input_file = os.path.join(test_folder, folder, 'input.txt')
            json_file = os.path.join(test_folder, folder, 'user.json')
            expected_result_file = os.path.join(test_folder, folder, 'expected_output.json')
            result_file = os.path.join(test_folder, folder, 'result.json')

            # 执行程序，将input.txt作为输入
            run_exe_with_input(exe_path, input_file, json_file)
            # 判断是否存在并比较result.json和expected_output.json
            # 使用json内容比较两个文件，忽略json文件成员的顺序
            with open(result_file, 'r') as f:
                result = json.load(f)
            with open(expected_result_file, 'r') as f:
                expected_result = json.load(f)
            if json.dumps(result, sort_keys=True) == json.dumps(expected_result, sort_keys=True):
                print(f"测试用例{folder}通过")
                successful_tests += 1
            else:
                failed_tests.append(folder)  # 如果测试失败，将测试用例名称添加到失败列表中

            total_files += 1

    print(f"总文件数量: {total_files}")
    print(f"成功的测试用例数量: {successful_tests}")
    print(f"失败的测试用例: {failed_tests}")  # 打印失败的测试用例名称
    # 全部通过
    if successful_tests == total_files:
        print("全部通过！！！！！！")
    else:
        print("未全部通过")

# 指定exe文件的路径
exe_path = r"cmake-build-debug\The_Rich.exe"

# 指定包含测试文件夹的路径
test_folder = r"test2"

# 运行比对程序输出和预期输出
compare_outputs(test_folder)
