import random
import subprocess

moves = ['u', 'r', 'f', 'l', 'b', 'd']


def creat_cube(name: str):
    res = subprocess.run(['cubesDataBase.exe', name], capture_output=True)
    print(res.stdout.decode())


def shuffle_cube(name: str, entropy: int):
    shuffle = ""
    for i in range(entropy):
        shuffle += moves[random.randint(0, len(moves) - 1)]
    print(shuffle)
    res = subprocess.run(['cubesDataBase.exe', name, shuffle], capture_output=True)
    print(res.stdout.decode())


if __name__ == "__main__":
    creat_cube("1234.cube")
    shuffle_cube("1234.cube", 100)
    creat_cube("1234.cube")


