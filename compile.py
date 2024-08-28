import argparse
import subprocess
import os

def execute_command(command, verbose=False):
    try:
        process = subprocess.run(command, shell=True, check=True, text=True, capture_output=True)
        if verbose: print("Command executed successfully!")
        if verbose: print("Output:", process.stdout)
        if process.stderr:
            if verbose: print("Error:", process.stderr)
    except subprocess.CalledProcessError as e:
        if verbose: print(f"Command failed with error: {e}")
        return

#DIR = os.path.join("/home", "joacaldo", "memoria", "mesher")
#DIR = os.path.join("/home", "joacaldo", "memoria", "mesher-reupload", "mesher")
DIR = os.path.join("/home", "joacaldo", "memoria", "MixedOcTree")


def compile_mesher(args):
    if args['clean']:
        execute_command(f"rm -rf {os.path.join(args['mesher_path'], 'build')}")
        execute_command(f"mkdir {os.path.join(args['mesher_path'], 'build')}")

    cmake_process = subprocess.Popen(["cmake", "../src/"], cwd=os.path.join(args['mesher_path'], "build"), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    #cmake_process.wait()  # Wait for cmake to finish
    cmake_output, cmake_error = cmake_process.communicate()

    if cmake_process.returncode == 0:
        if args['verbose']: print(cmake_output)

        make_process = subprocess.Popen(["make"], cwd=os.path.join(args['mesher_path'], "build"), shell=True,
                                        stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                        universal_newlines=True)
        make_output, make_error = make_process.communicate()

        if make_process.returncode == 0:
            if args['verbose']: print(make_output)
            make_output = make_output.strip()

            if make_output.endswith("[100%] Built target mesher_roi"):
                print("Compiled successfully")
    else:
        print(f"cmake error: {cmake_error}")
        print(f"Error during cmake: {cmake_process.returncode}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compile mesher")
    parser.add_argument("-v", "--verbose", default=False, required=False, help="Verbose", action=argparse.BooleanOptionalAction)
    parser.add_argument("-c", "--clean", required=False, help="Boolean to make clean compilation", action=argparse.BooleanOptionalAction)
    parser.add_argument("-m", "--mesher-path", required=True, help="Mesher path to be compiled", type=str)
    args_pars = parser.parse_args()

    args = vars(args_pars)

    #print(args)

    compile_mesher(args)