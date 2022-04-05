import sys
import os
import subprocess

# check number of arguments
if len(sys.argv) != 2:
    print(f"usage: python3 {sys.argv[0]} testsfolder")
    exit(1)

# check test folder
cwd = os.getcwd()
test_dir_path = os.path.join(cwd, sys.argv[1])
if not os.path.isdir(test_dir_path):
    print(f"error: {test_dir_path} is not a valid directory")
    exit(1)

# get compiler folder
parent_dir_path = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
compiler_dir_path = os.path.join(parent_dir_path, "compiler")
if not os.path.isdir(compiler_dir_path):
    print("error: compiler folder not found")
    exit(1)

# get compiler binary
compiler_bin_path = os.path.join(compiler_dir_path, "ifcc")
if not os.path.isfile(compiler_bin_path):
    print("error: compiler binary not found")
    exit(1)

# get all tests files
test_files = os.listdir(test_dir_path)
test_files.sort()

# init variables to get statistics
nb_tests_total = len(test_files)
nb_tests_ok = 0
nb_tests_ko = 0
nb_tests_skipped = 0
tests_ko = []

# do test for each file
for f in test_files:
    print(f"Testing {f}...", end=" ")

    # get file absolute path
    current_file_path = os.path.join(test_dir_path, f)

    # compile to check if program is valid
    command = " ".join([compiler_bin_path, current_file_path])
    pipe = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    pipe.communicate()
    if pipe.returncode == 0:
        # run valgrind to check memory leaks
        command = " ".join(["valgrind", compiler_bin_path, current_file_path])
        pipe = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pipe.communicate()

        if pipe.returncode == 0:
            print("OK")
            nb_tests_ok += 1
        else:
            print("INVALID")
            nb_tests_ko += 1
            tests_ko.append(f)
    else:
        print("SKIPPED")
        nb_tests_skipped += 1

# print statistics
print("")
print(f"Number of tests:            {nb_tests_total}")
print(f"Number of tests OK:         {nb_tests_ok}")
print(f"Number of tests KO:         {nb_tests_ko}")
print(f"Number of skipped tests:    {nb_tests_skipped}")
if (nb_tests_ko > 0):
    print("Tests KO:")
    for f in tests_ko:
        print(f" - {f}")