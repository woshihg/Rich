import os
import subprocess
import json
import argparse

def run_exe_with_input(exe_path, input_file, json_file):
    try:
        print(f"Running {exe_path} with arguments {json_file} and {input_file}")
        with open(input_file, 'r') as f:
            input_data = f.read()
        input_data = input_data + '\nquit\n'
        process = subprocess.run([exe_path, json_file, 'richman'], input=input_data, text=True, capture_output=True, timeout=10, encoding='gbk')

        print(process.stdout)
    except subprocess.TimeoutExpired:
        print("Process timed out.")
    except Exception as e:
        print(f"An error occurred: {e}")

def compare_outputs(test_folder, exe_path):
    total_files = 0
    successful_tests = 0
    failed_tests = []

    for folder in os.listdir(test_folder):
        folder_path = os.path.join(test_folder, folder)
        if os.path.isdir(folder_path):
            input_file = os.path.join(folder_path, 'input.txt')
            json_file = os.path.join(folder_path, 'user.json')
            expected_result_file = os.path.join(folder_path, 'expected_output.json')
            result_file = os.path.join(folder_path, 'result.json')

            if all(map(os.path.exists, [input_file, json_file, expected_result_file])):
                run_exe_with_input(exe_path, input_file, json_file)

                with open(result_file, 'r') as f:
                    result = json.load(f)
                with open(expected_result_file, 'r') as f:
                    expected_result = json.load(f)

                if result == expected_result:
                    print(f"Test case {folder} passed")
                    successful_tests += 1
                else:
                    failed_tests.append(folder)

                total_files += 1

    print(f"Total files: {total_files}")
    print(f"Successful test cases: {successful_tests}")
    print(f"Failed test cases: {failed_tests}")

    if successful_tests == total_files:
        print("All tests passed!")
    else:
        print("Not all tests passed.")

def run_tests(exe_path, test_folder):
    compare_outputs(test_folder, exe_path)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run tests with an executable file.')
    parser.add_argument('exe_path', type=str, help='Path to the executable file')
    parser.add_argument('test_folder', type=str, help='Path to the folder containing test files')
    args = parser.parse_args()

    run_tests(args.exe_path, args.test_folder)
