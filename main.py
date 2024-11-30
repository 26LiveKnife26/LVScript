import os
import time
import sys
IMPORTS = ["lime"]
lime_import = False
def interpret(FILE_NAME):
    with open("%s.lvs" % FILE_NAME, "r") as SCRIPT:
        for line in SCRIPT.readlines():
            if "put; " in line:
                print(line.replace("put; ", ""), end = "")
            elif "put;on; " in line:
                input(line.replace("put;on; ", ""))
            elif "put;len; " in line:
                print(len(line.replace("put;len; ", "")))
            elif "put;os; " in line:
                os.system(line.replace("put;os; ", ""))
            elif "s;" in line:
                print("LVS: LVS Target OFF")
                exit("")
            elif "error; " in line:
                print("LVS: Error: %s" % line.replace("error; ", ""))
            elif "sleep; " in line:
                try:
                    time.sleep(int(line.replace("sleep; ", "")))
                except:
                    print("LVS: Time Error: enter a INT-value")
            elif "n;" in line:
                print("\n")
            elif "clear;" in line:
                print("\033[0d\033[2J", end = "")
            elif "after;" in line:
                pass
            elif "//" in line:
                pass
            elif "pver;" in line:
                print(f"{sys.version_info.major}.{sys.version_info.minor}.{sys.version_info.micro}")
            elif "ver;" in line:
                print("1.0")
            elif "protocol; " in line:
                print("LVSProtocol 1.0 - CODING PROTOCOL")
            elif "coding;" in line:
                print("UTF-8")
            elif "int;" in line:
                print("GCC/G++ Python - LVScript Interpreteter 1.0")
            elif "#import " in line:
                if line.replace("#import ", "").replace(" ", "").lower() in IMPORTS:
                    lime_import = True
                else:
                    print("LVS: Import Error: not find a %s" % line.replace("#import ", ""))
            elif "#include" in line:
                print("Bruh =\. This is not C, this is LVScript ¯ \ _ (ツ) _ / ¯. Hohoho =)")
    SCRIPT.close()
if __name__ == "__main__":
    interpret("main")
    print("")