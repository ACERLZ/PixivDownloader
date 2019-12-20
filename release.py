import os
import platform

if __name__ == "__main__":
    if platform.system() == "Windows":
        print("[+] Release type -> Darwin")
        os.chdir("build")
        os.system("windeployqt PixivDownloader.exe")
        os.system("del *.o *.h *.cpp *.stash Makefile")
        os.system("7z a PixivDownloader-windows.zip *")
        print("[+] Release Windows -> Done")
    elif platform.system() == "Darwin":
        print("[+] Release type -> Darwin")
        os.chdir("build")
        os.system("macdeployqt PixivDownloader.app")
        os.system("rm -rf *.o *.h *.cpp *.stash Makefile")
        os.system("zip -r PixivDownloader-osx.zip PixivDownloader.app")
        print("[+] Release Darwin -> Done")
    elif platform.system() == "Linux":
        print("[+] Release type -> Linux")
        os.chdir("build")
        os.system("rm -rf *.o *.h *.cpp *.stash Makefile")
        os.system("zip -r PixivDownloader-linux.zip *")
        print("[+] Release Linux -> Done")