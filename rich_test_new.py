import os
import time
import filecmp
import subprocess
import json

def run_exe_with_input(exe_path, input_file):
    try:
        process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        process.stdin.write(open(input_file, 'rb').read())
        process.stdin.flush()  # 刷新输入缓冲区
    except Exception as e:
        print(f"An error occurred: {e}")

def compare_outputs(test_folder):
    total_files = 0
    successful_tests = 0

    for folder in os.listdir(test_folder):
        if os.path.isdir(os.path.join(test_folder, folder)):
            input_file = os.path.join(test_folder, folder, 'input.txt')
            expected_output_file = os.path.join(test_folder, folder, 'expected_output.txt')
            expected_result_file = os.path.join(test_folder, folder, 'expected_output.json')
            output_file = os.path.join(test_folder, folder, 'output.txt')
            result_file = os.path.join(test_folder, folder, 'result.json')

            # 执行程序，将input.txt作为输入
            run_exe_with_input(exe_path, input_file)
            # 等待1S
            time.sleep(1)
            # 比较output.txt和expectedoutput.txt以及result.json和expected_output.json
            if filecmp.cmp(output_file, expected_output_file) and filecmp.cmp(result_file, expected_result_file):
                print(f"测试文件夹 {folder} 的输出与预期一致")
                successful_tests += 1

            total_files += 1

    print(f"总文件数量: {total_files}")
    print(f"成功的测试用例数量: {successful_tests}")

# 指定exe文件的路径
exe_path = r"cmake-build-debug\The_Rich.exe"

# 指定包含测试文件夹的路径
test_folder = r"Test"

# 运行比对程序输出和预期输出
compare_outputs(test_folder)
