import argparse
import os
import subprocess

from compile import execute_command, compile_mesher

MESHER = "/home/joacaldo/memoria/mesher/build/mesher_roi" #"/home/joacaldo/memoria/meshert/build/mesher_roi"
MESHER_TEST = "/home/joacaldo/memoria/mesher/build_test/mesher_roi_tests" #/home/joacaldo/memoria/meshert/build_test/mesher_roi_tests"
MESHER_P = "/home/joacaldo/memoria/MixedOcTree/build/mesher_roi"
MESHER_T = "/home/joacaldo/memoria/mesher-reupload/mesher/build/mesher_roi"

VIEWER = "/home/joacaldo/memoria/view210907/build/viewer"

DATA_PATH = "/home/joacaldo/memoria/data"

def run_mesher(args):
    assert not (args['allrl'] is None) or not (args['surfacerl'] is None), "At least one refinement level must be specified"

    if args['mesher'] == "t":
        mesher = MESHER_T
        out_dir = os.path.join(DATA_PATH, "out_tamara")
    elif args['mesher'] == "p":
        mesher = MESHER_P
        out_dir = os.path.join(DATA_PATH, "out_profe")
    elif args['mesher'] == "j":
        mesher = MESHER
        out_dir = os.path.join(DATA_PATH, "out")
    elif args['mesher'] == "test":
        mesher = MESHER_TEST
        out_dir = os.path.join(DATA_PATH, "out_tests")
    else:
        print("Invalid mesher option")
        return
    
    if args['compile']:
        args['mesher_path'] = os.path.dirname(os.path.dirname(mesher))
        compile_mesher(args)

    if args['allrl'] is not None:
        out_rl_name = f"a{args['allrl']}"
        command_rl = f"-a {args['allrl']}"

    elif args['surfacerl'] is not None:
        out_rl_name = f"s{args['surfacerl']}"
        command_rl = f"-s {args['surfacerl']}"

    filename = os.path.join(DATA_PATH, "inputs", args['input'])
    output_filename = f"{args['input']}_{out_rl_name}"

    output_filepath = os.path.join(out_dir, output_filename)

    # # Construct the command using the arguments
    command = f"{mesher} -o {filename}.off -u {output_filepath} {command_rl}"

    # Check if filename exists
    if not os.path.exists(filename + ".off"):
        print(f"File {filename}.off does not exist.")
        return

    print(command)

    # Execute the command
    execute_command(command, verbose=args['verbose'])
    
    print(f"File saved to {output_filepath}.vtk")

if __name__ == "__main__":
    # Set up argument parsing
    parser = argparse.ArgumentParser(description="Run mesher_roi with specified parameters.")
    parser.add_argument("-m", "--mesher", default="j", type=str, required=False, help="Choose between Profe's, Tamara's and Joaquin's mesher")
    #parser.add_argument("-p", "--profe", default=False, required=False, help="Use profe's mesher", action=argparse.BooleanOptionalAction)
    parser.add_argument("-o", "--input", type=str, required=True, help="Input filename")
    parser.add_argument("-s", "--surfacerl", type=int, required=False, help="Surface refinement level")
    parser.add_argument("-a", "--allrl", type=int, required=False, help="All refinement level")
    parser.add_argument("-c", "--compile", default=False, help="Compile code", action=argparse.BooleanOptionalAction)
    parser.add_argument("-v", "--verbose", default=False, required=False, help="Verbose", action=argparse.BooleanOptionalAction)
    

    # Compilation parameters
    parser.add_argument("-vc", "--verbose-compilation", default=False, required=False, help="Verbose compilation", action=argparse.BooleanOptionalAction)
    parser.add_argument("-cc", "--clean-compilation", required=False, default=False, help="Make clean compilation", action=argparse.BooleanOptionalAction)
    parser.add_argument("-ct", "--compile-test", required=False, default=False, help="Make clean compilation", action=argparse.BooleanOptionalAction)
    parser.add_argument("-cmk", "--cmake", required=False, default=False, help="Make Cmake", action=argparse.BooleanOptionalAction)
    #parser.add_argument("-m", "--mesher-path", required=False, help="Mesher path to be compiled", type=str)
    
    #python run_mesher.py -m test -o space -s 1 -c -vc -v -cc -ct  (Use -s or -a: i.e: -a 4)

    # Parse arguments
    args_pars = parser.parse_args()

    args = vars(args_pars)

    run_mesher(args)
