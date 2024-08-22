import argparse
import os
import subprocess

MESHER = "/home/joacaldo/memoria/MixedOcTree/mesher_roi"
MESHER_T = "/home/joacaldo/memoria/mesher-reupload/mesher/build/mesher_roi"

VIEWER = "/home/joacaldo/memoria/view210907/build/viewer"

DATA_PATH = "/home/joacaldo/memoria/data/util/"
DATA_OUT_PATH = "/home/joacaldo/memoria/data/"

def execute_command(command):
    try:
        process = subprocess.run(command, shell=True, check=True, text=True, capture_output=True)
        print("Command executed successfully!")
        print("Output:", process.stdout)
        if process.stderr:
            print("Error:", process.stderr)
    except subprocess.CalledProcessError as e:
        print(f"Command failed with error: {e}")
        return

def run_mesher(args):
    if args['tamara']:
        mesher = MESHER_T
        out_dir = DATA_OUT_PATH + "out_tamara/"
    else:
        mesher = MESHER
        out_dir = DATA_OUT_PATH + "out/"

    filename = f"{DATA_PATH}{args['input']}"
    output_filename = f"{args['input']}_s{args['surface']}"

    output_filepath = f"{out_dir}{output_filename}"

    # # Construct the command using the arguments
    command = f"{mesher} -o {filename}.off -u {output_filepath} -s {args['surface']}"

    # Check if filename exists
    if not os.path.exists(filename + ".off"):
        print(f"File {filename}.off does not exist.")
        return


    print(command)

    # Execute the command
    execute_command(command)
    
    print(f"File saved to {output_filepath}.vtk")

if __name__ == "__main__":
    # Set up argument parsing
    parser = argparse.ArgumentParser(description="Run mesher_roi with specified parameters.")
    parser.add_argument("-t", "--tamara", default=False, required=False, help="Use tamara's mesher", action=argparse.BooleanOptionalAction)
    parser.add_argument("-o", "--input", type=str, required=True, help="Input filename")
    parser.add_argument("-s", "--surface", type=int, required=True, help="Surface refinement level")
    
    # Parse arguments
    args_pars = parser.parse_args()

    args = vars(args_pars)

    run_mesher(args)
