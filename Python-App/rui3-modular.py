import tkinter as tk
from tkinter import scrolledtext
import tkinter.ttk as ttk
from tkinter import messagebox
import shutil
import os
from os import listdir
import glob
import stat
import subprocess
from subprocess import Popen, PIPE, STDOUT
import time
from sys import platform
import serial.tools.list_ports

# Variables
arduino_cli_cmd = "./arduino-cli_0.27.1_Windows_64bit/arduino-cli.exe"

compile_command = ""

upload_port = ""

installation_complete = False

rak3172_board = "rak_rui:stm32:WisDuoRAK3172EvaluationBoard"
rak4631_board = "rak_rui:nrf52:WisCoreRAK4631Board"
selected_board = ""

rak1901 = False
rak1902 = False
rak1903 = False
rak1904 = False
rak1904_slot = 'A'
rak1905 = False
rak1905_slot = 'A'
rak1906 = False
rak1921 = False
rak12002 = False
rak12003 = False
rak12010 = False
rak12014 = False
rak12014_slot = 'A'
rak12019 = False
rak12027 = False
rak12027_slot = 'A'
rak12037 = False
rak12039 = False
rak12040 = False
rak12047 = False
rak12500 = False
rak13011 = False
rak13011_slot = 'A'
rak3172 = False
rak4631 = False

selected_slot = 'A'


def serial_ports():
    return serial.tools.list_ports.comports()


def on_select(event=None):
    global upload_port
    # get selection from event
    print("event.widget:", event.widget.get())

    # or get selection directly from combobox
    print("comboboxes: ", port_selector_cb.get())

    port_split = port_selector_cb.get()

    upload_port = port_split.split()[0]

    print("Selected: ", upload_port)
    return


def slot_a_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'A'
    print("Selected Slot A for module ")
    get_slot_window.destroy()
    return


def slot_b_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'B'
    print("Selected Slot B for module ")
    get_slot_window.destroy()
    return


def slot_c_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'C'
    print("Selected Slot C for module ")
    get_slot_window.destroy()
    return


def slot_d_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'D'
    print("Selected Slot D for module ")
    get_slot_window.destroy()
    return


def slot_e_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'E'
    print("Selected Slot E for module ")
    get_slot_window.destroy()
    return


def slot_f_cb():
    global get_slot_window
    global selected_slot
    selected_slot = 'F'
    print("Selected Slot F for module ")
    get_slot_window.destroy()
    return


def ask_slot(module):
    global selected_module
    global get_slot_window
    selected_module = module
    get_slot_window = tk.Toplevel(main_window)
    get_slot_window.geometry("300x500")
    slot_a_bt = tk.Button(get_slot_window, text="Slot A", command=slot_a_cb)
    slot_a_bt.pack()
    slot_b_bt = tk.Button(get_slot_window, text="Slot B", command=slot_b_cb)
    slot_b_bt.pack()
    slot_c_bt = tk.Button(get_slot_window, text="Slot C", command=slot_c_cb)
    slot_c_bt.pack()
    slot_d_bt = tk.Button(get_slot_window, text="Slot D", command=slot_d_cb)
    slot_d_bt.pack()
    slot_e_bt = tk.Button(get_slot_window, text="Slot E", command=slot_e_cb)
    slot_e_bt.pack()
    slot_f_bt = tk.Button(get_slot_window, text="Slot F", command=slot_f_cb)
    slot_f_bt.pack()


def remove_source(module_bt, source_name):
    print(source_name)
    module_bt.config(bg="salmon")
    fileList = glob.glob("../"+source_name+"*")
    # Iterate over the list of filepaths & remove each file.
    for filePath in fileList:
        try:
            os.remove(filePath)
        except:
            print("Error while deleting file : ", filePath)
    return False


def enable_source(module_bt, source_name, header_name=""):
    module_bt.config(bg="lime")
    shutil.copy("../module-files/"+source_name, "../")
    if not (header_name == ""):
        shutil.copy("../module-files/"+header_name, "../")
    return True


def rak1901_cb():
    global rak1901
    global rak1901_bt
    if (rak1901):
        rak1901 = remove_source(rak1901_bt, "RAK1901")
    else:
        rak1901 = enable_source(rak1901_bt, "RAK1901_temp.cpp")
    return


def rak1902_cb():
    global rak1902
    global rak1902_bt
    if (rak1902):
        rak1902 = remove_source(rak1902_bt, "RAK1902")
    else:
        rak1902 = enable_source(rak1902_bt, "RAK1902_press.cpp")
    return


def rak1903_cb():
    global rak1903
    global rak1903_bt
    if (rak1903):
        rak1903 = remove_source(rak1903_bt, "RAK1902")
    else:
        rak1903 = enable_source(rak1903_bt, "RAK1903_light.cpp")
    return


def rak1904_cb():
    global rak1904
    global rak1904_bt
    global rak1904_slot
    header_name = "RAK1904_acc_S_"
    if (rak1904):
        rak1904 = remove_source(rak1904_bt, "RAK1904")
    else:
        ask_slot(rak1904)
        main_window.wait_window(get_slot_window)
        if (selected_slot == 'A'):
            rak1904_slot = 'A'
            header_name = header_name + "A.h"
        elif (selected_slot == 'B'):
            rak1904_slot = 'B'
            header_name = header_name + "B.h"
        elif (selected_slot == 'C'):
            rak1904_slot = 'C'
            header_name = header_name + "C.h"
        elif (selected_slot == 'D'):
            rak1904_slot = 'D'
            header_name = header_name + "D.h"
        elif (selected_slot == 'E'):
            rak1904_slot = 'E'
            header_name = header_name + "E.h"
        elif (selected_slot == 'F'):
            rak1904_slot = 'F'
            header_name = header_name + "F.h"
        rak1904 = enable_source(rak1904_bt, "RAK1904_acc.cpp", header_name)
    return


def rak1905_cb():
    global rak1905
    global rak1905_bt
    global rak1905_slot
    header_name = "RAK1905_9dof_S_"

    if (rak1905):
        rak1905 = remove_source(rak1905_bt, "RAK1905")
    else:
        ask_slot(rak1905)
        main_window.wait_window(get_slot_window)
        if (selected_slot == 'A'):
            rak1905_slot = 'A'
            header_name = header_name + "A.h"
        elif (selected_slot == 'B'):
            rak1905_slot = 'B'
            header_name = header_name + "B.h"
        elif (selected_slot == 'C'):
            rak1905_slot = 'C'
            header_name = header_name + "C.h"
        elif (selected_slot == 'D'):
            rak1905_slot = 'D'
            header_name = header_name + "D.h"
        elif (selected_slot == 'E'):
            rak1905_slot = 'E'
            header_name = header_name + "E.h"
        elif (selected_slot == 'F'):
            rak1905_slot = 'F'
            header_name = header_name + "F.h"
        rak1905 = enable_source(rak1905_bt, "RAK1905_9dof.cpp", header_name)
    return


def rak1906_cb():
    global rak1906
    global rak1906_bt
    if (rak1906):
        rak1906 = remove_source(rak1906_bt, "RAK1906")
    else:
        rak1906 = enable_source(rak1906_bt, "RAK1906_env.cpp")
    return


def rak1921_cb():
    global rak1921
    global rak1921_bt
    if (rak1921):
        rak1921 = remove_source(rak1921_bt, "RAK1905")
    else:
        rak1921 = enable_source(rak1921_bt, "RAK1921_display.cpp")
    return


def rak12002_cb():
    global rak12002
    global rak12002_bt
    if (rak12002):
        rak12002 = remove_source(rak12002_bt, "RAK12002")
    else:
        rak12002 = enable_source(rak12002_bt, "RAK12002_rtc.cpp")
    return


def rak12003_cb():
    global rak12003
    global rak12003_bt
    if (rak12003):
        rak12003 = remove_source(rak12003_bt, "RAK12003")
    else:
        rak12003 = enable_source(rak12003_bt, "RAK12003_fir.cpp")
    return


def rak12010_cb():
    global rak12010
    global rak12010_bt
    if (rak12010):
        rak12010 = remove_source(rak12010_bt, "RAK12010")
    else:
        rak12010 = enable_source(rak12010_bt, "RAK12010_light.cpp")
    return


def rak12014_cb():
    global rak12014
    global rak12014_bt
    global rak12014_slot
    header_name = "RAK12014_tof_S_"

    if (rak12014):
        rak12014 = remove_source(rak12014_bt, "RAK12014")
    else:
        ask_slot(rak12014)
        main_window.wait_window(get_slot_window)
        if (selected_slot == 'A'):
            rak12014_slot = 'A'
            header_name = header_name + "A.h"
        elif (selected_slot == 'B'):
            rak12014_slot = 'B'
            header_name = header_name + "B.h"
        elif (selected_slot == 'C'):
            rak12014_slot = 'C'
            header_name = header_name + "C.h"
        elif (selected_slot == 'D'):
            rak12014_slot = 'D'
            header_name = header_name + "D.h"
        elif (selected_slot == 'E'):
            rak12014_slot = 'E'
            header_name = header_name + "E.h"
        elif (selected_slot == 'F'):
            rak12014_slot = 'F'
            header_name = header_name + "F.h"
        rak12014 = enable_source(rak12014_bt, "RAK12014_tof.cpp", header_name)
    return


def rak12019_cb():
    global rak12019
    global rak12019_bt
    if (rak12019):
        rak12019 = remove_source(rak12019_bt, "RAK12019")
    else:
        rak12019 = enable_source(rak12019_bt, "RAK12019_uv.cpp")
    return


def rak12027_cb():
    global rak12027
    global rak12027_bt
    global rak12027_slot
    header_name = "RAK12027_seismic_S_"

    if (rak12027):
        rak12027 = remove_source(rak12027_bt, "RAK12027")
    else:
        ask_slot(rak12027)
        main_window.wait_window(get_slot_window)
        if (selected_slot == 'A'):
            rak12027_slot = 'A'
            header_name = header_name + "A.h"
        elif (selected_slot == 'B'):
            rak12027_slot = 'B'
            header_name = header_name + "B.h"
        elif (selected_slot == 'C'):
            rak12027_slot = 'C'
            header_name = header_name + "C.h"
        elif (selected_slot == 'D'):
            rak12027_slot = 'D'
            header_name = header_name + "D.h"
        elif (selected_slot == 'E'):
            rak12027_slot = 'E'
            header_name = header_name + "E.h"
        elif (selected_slot == 'F'):
            rak12027_slot = 'F'
            header_name = header_name + "F.h"
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", header_name)
    return


def rak12037_cb():
    global rak12037
    global rak12037_bt
    if (rak12037):
        rak12037 = remove_source(rak12037_bt, "RAK12037")
    else:
        rak12037 = enable_source(rak12037_bt, "RAK12037_co2.cpp")
    return


def rak12039_cb():
    global rak12039
    global rak12039_bt
    if (rak12039):
        rak12039 = remove_source(rak12039_bt, "RAK12039")
    else:
        rak12039 = enable_source(rak12039_bt, "RAK12039_pm.cpp")
    return


def rak12040_cb():
    global rak12040
    global rak12040_bt
    if (rak12040):
        rak12040 = remove_source(rak12040_bt, "RAK12040")
    else:
        rak12040 = enable_source(rak12040_bt, "RAK12040_temp_arr.cpp")
    return


def rak12047_cb():
    global rak12047
    global rak12047_bt
    if (rak12047):
        rak12047 = remove_source(rak12047_bt, "RAK12047")
    else:
        rak12047 = enable_source(rak12047_bt, "RAK12047_voc.cpp")
    return


def rak12500_cb():
    global rak12500
    global rak12500_bt
    if (selected_board == "rak_rui:stm32:WisDuoRAK3172EvaluationBoard"):
        messagebox.showerror(
            "ERROR", "RAK3172 does not support RAK12500 (yet)")
        rak12500 = False
        rak12500_bt.config(bg="salmon")
        os.remove("../rak12500_gnss.cpp")
        return
    if (rak12500):
        rak12500 = remove_source(rak12500_bt, "RAK12500")
    else:
        rak12500 = enable_source(rak12500_bt, "rak12500_gnss.cpp")
    return


def rak13011_cb():
    global rak13011
    global rak13011_bt
    global rak13011_slot
    header_name = "RAK13011_switch_S_"

    if (rak13011):
        rak13011 = remove_source(rak13011_bt, "RAK13011")
    else:
        ask_slot(rak13011)
        main_window.wait_window(get_slot_window)
        if (selected_slot == 'A'):
            rak13011_slot = 'A'
            header_name = header_name + "A.h"
        elif (selected_slot == 'B'):
            rak13011_slot = 'B'
            header_name = header_name + "B.h"
        elif (selected_slot == 'C'):
            rak13011_slot = 'C'
            header_name = header_name + "C.h"
        elif (selected_slot == 'D'):
            rak13011_slot = 'D'
            header_name = header_name + "D.h"
        elif (selected_slot == 'E'):
            rak13011_slot = 'E'
            header_name = header_name + "E.h"
        elif (selected_slot == 'F'):
            rak13011_slot = 'F'
            header_name = header_name + "F.h"
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", header_name)
    return


def rak3172_cb():
    global selected_board
    global rak4631
    global rak3172
    selected_board = rak3172_board
    rak3172 = True
    rak4631 = False
    rak3172_bt.config(bg="lime")
    rak4631_bt.config(bg="salmon")
    return


def rak4631_cb():
    global selected_board
    global rak4631
    global rak3172
    selected_board = rak4631_board
    rak3172 = False
    rak4631 = True
    rak3172_bt.config(bg="salmon")
    rak4631_bt.config(bg="lime")
    return


def ext_app_to_log(command, headline, clear):
    if clear:
        output_field.delete("1.0", "end")
        output_field.update()
    output_field.insert(tk.END, headline)
    output_field.insert(tk.END, "\n\n")
    output_field.focus()
    output_field.update()
    output_field.update_idletasks()

    proc = subprocess.Popen(command,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT,
                            universal_newlines=True,
                            bufsize=0)

    # proc.communicate()
    # output_field.insert(tk.END, proc.communicate())

    while True:
        line = proc.stdout.readline()
        if not line:
            break
        output_field.insert(tk.END, line)
        # this triggers an update of the text area, otherwise it doesn't update
        output_field.update()
        output_field.update_idletasks()
        output_field.see(tk.END)

    # Wait until process terminates (without using p.wait())
    while proc.poll() is None:
        # Process hasn't exited yet, let's wait some
        time.sleep(0.5)

    result = proc.returncode

    print("Finished " + command + " Result " + str(result))

    return result


def verify_cb():
    global selected_board

    if (not installation_complete):
        messagebox.showerror("ERROR", "Installation required first")
        return
    if (selected_board == ""):
        messagebox.showerror("ERROR", "Select a board first")
        return

    verify_bt.config(text="busy", bg="salmon")
    result_bt.config(bg="dodgerblue", text="Result")

    compile_command = arduino_cli_cmd + " compile -b " + selected_board + \
        " --output-dir ../flash-files --build-path ../build --build-cache-path ../cache --no-color --verbose --library ../libraries ../RUI3-Modular.ino"
    headline = "Verify, this can take some time, be patient"
    return_code = ext_app_to_log(compile_command, headline, True)

    if (return_code == 0):
        result_bt.config(bg="lime", text="SUCCESS")
    else:
        result_bt.config(bg="salmon", text="FAIL")

    verify_bt.config(text="Verify", bg="dodgerblue")

    return


def compile_cb():
    global selected_board

    if (not installation_complete):
        messagebox.showerror("ERROR", "Installation required first")
        return
    if (selected_board == ""):
        messagebox.showerror("ERROR", "Select a board first")
        return
    if (upload_port == ""):
        messagebox.showerror("ERROR", "Select an upload port first")
        return

    compile_bt.config(text="busy", bg="salmon")
    result_bt.config(bg="dodgerblue", text="Result")

    compile_command = arduino_cli_cmd + " compile -b " + selected_board + \
        " --output-dir ../flash-files --build-path ../build --build-cache-path ../cache --upload -p " + \
        upload_port + " --no-color --verbose --library ../libraries ../RUI3-Modular.ino"

    headline = "Download, this can take some time, be patient"
    return_code = ext_app_to_log(compile_command, headline, True)

    if (return_code == 0):
        result_bt.config(bg="lime", text="SUCCESS")
    else:
        result_bt.config(bg="salmon", text="FAIL")

    compile_bt.config(text="Download", bg="dodgerblue")

    return


def clean_build_cb():
    clean_bt.config(text="busy", bg="salmon")

    if os.path.exists("../build"):
        shutil.rmtree("../build")
    if os.path.exists("../cache"):
        shutil.rmtree("../cache")
    if os.path.exists("../flash-files"):
        shutil.rmtree("../flash-files")

    clean_bt.config(text="Clean", bg="dodgerblue")
    return


def refresh_installation():
    global installation_complete

    install_bt.config(text="busy", bg="salmon")
    result_bt.config(bg="dodgerblue", text="Result")

    compile_command = arduino_cli_cmd + " config delete board_manager.additional_urls"
    headline = "Cleaning up additional BSP URL's"
    return_code1 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    compile_command = arduino_cli_cmd + \
        " config add board_manager.additional_urls https://raw.githubusercontent.com/beegee-tokyo/test/main/beegee-patch-rui3.json"
    # compile_command = arduino_cli_cmd + " config add board_manager.additional_urls https://raw.githubusercontent.com/RAKWireless/RAKwireless-Arduino-BSP-Index/staging/RUI_3.5.3/package_rakwireless.com_rui_index.json"

    headline = "Installing additional BSP URL's"
    return_code1 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    compile_command = arduino_cli_cmd + " core update-index"
    headline = "Updating BSP's index"
    return_code2 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    compile_command = arduino_cli_cmd + " core install rak_rui:nrf52"
    headline = "Installing RAK4630 BSP, this can take quite some time"
    return_code4 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    compile_command = arduino_cli_cmd + " core install rak_rui:stm32"
    headline = "Installing RAK3172 BSP, this can take quite some time"
    return_code3 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    result = False
    if (return_code1 == 0) and (return_code2 == 0) and (return_code3 == 0) and (return_code4 == 0):
        result_bt.config(bg="lime", text="SUCCESS")
        with open('./.bsp', 'w') as f:
            f.write('Installation success!')
            f.close()
        installation_complete = True
        result = True
    else:
        result_bt.config(bg="salmon", text="FAIL")

    install_bt.config(text="Refresh\nInstallation!", bg="lime")

    return result


def check_installation():
    result = False
    if os.path.exists("./.bsp"):
        result = True
    else:
        if (refresh_installation() == 0):
            install_bt.destroy()
    return result


def check_config():
    if os.path.exists("./.config"):
        # read last config
        print("Get last config")
        with open('./.config', 'r') as f:
            while True:
                line = f.readline()
                if not line:
                    break
                line = line.rstrip()
                print("Got >>" + line + "<<")
                get_last_config(line)
            f.close()
    return


def get_last_config(check_line):
    global selected_board
    global rak1901
    global rak1902
    global rak1903
    global rak1904
    global rak1904_slot
    global rak1905
    global rak1905_slot
    global rak1906
    global rak1921
    global rak12002
    global rak12003
    global rak12010
    global rak12014
    global rak12014_slot
    global rak12019
    global rak12027
    global rak12037
    global rak12039
    global rak12040
    global rak12047
    global rak12500
    global rak13011
    global rak4631
    global rak3172
    if check_line == 'RAK1901':
        rak1901 = enable_source(rak1901_bt, "RAK1901_temp.cpp")
    elif check_line == 'RAK1902':
        rak1902 = enable_source(rak1902_bt, "RAK1902_press.cpp")
    elif check_line == "RAK1903":
        rak1903 = enable_source(rak1903_bt, "RAK1903_light.cpp")
    elif check_line == "RAK1904A":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_A.h")
    elif check_line == "RAK1904B":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_B.h")
    elif check_line == "RAK1904C":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_C.h")
    elif check_line == "RAK1904D":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_D.h")
    elif check_line == "RAK1904E":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_E.h")
    elif check_line == "RAK1904F":
        rak1904 = enable_source(
            rak1904_bt, "RAK1904_acc.cpp", "RAK1904_acc_S_F.h")
    elif check_line == "RAK1905A":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_A.h")
    elif check_line == "RAK1905B":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_B.h")
    elif check_line == "RAK1905C":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_C.h")
    elif check_line == "RAK1905D":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_D.h")
    elif check_line == "RAK1905E":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_E.h")
    elif check_line == "RAK1905F":
        rak1905 = enable_source(
            rak1905_bt, "RAK1905_9dof.cpp", "RAK1905_9dof_S_F.h")
    elif check_line == "RAK1906":
        rak1906 = enable_source(rak1906_bt, "RAK1906_env.cpp")
    elif check_line == "RAK1921":
        rak1921 = enable_source(rak1921_bt, "RAK1921_display.cpp")
    elif check_line == "RAK12002":
        rak12002 = enable_source(rak12002_bt, "RAK12002_rtc.cpp")
    elif check_line == "RAK12003":
        rak12003 = enable_source(rak12003_bt, "RAK12003_fir.cpp")
    elif check_line == "RAK12010":
        rak12010 = enable_source(rak12010_bt, "RAK12010_light.cpp")
    elif check_line == "RAK12014A":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_A.h")
    elif check_line == "RAK12014B":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_B.h")
    elif check_line == "RAK12014C":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_C.h")
    elif check_line == "RAK12014D":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_D.h")
    elif check_line == "RAK12014E":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_E.h")
    elif check_line == "RAK12014F":
        rak12014 = enable_source(
            rak12014_bt, "RAK12014_tof.cpp", "RAK12014_tof_S_F.h")
    elif check_line == "RAK12019":
        rak12019 = enable_source(rak12019_bt, "RAK12019_uv.cpp")
    elif check_line == "RAK12027A":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_A.h")
    elif check_line == "RAK12027B":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_B.h")
    elif check_line == "RAK12027C":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_C.h")
    elif check_line == "RAK12027D":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_D.h")
    elif check_line == "RAK12027E":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_E.h")
    elif check_line == "RAK12027F":
        rak12027 = enable_source(
            rak12027_bt, "RAK12027_seismic.cpp", "RAK12027_seismic_S_F.h")
    elif check_line == "RAK12037":
        rak12037 = enable_source(rak12037_bt, "RAK12037_co2.cpp")
    elif check_line == "RAK12040":
        rak12040 = enable_source(rak12040_bt, "RAK12040_temp_arr.cpp")
    elif check_line == "RAK12047":
        rak12047 = enable_source(rak12047_bt, "RAK12047_voc.cpp")
    elif check_line == "RAK12500":
        rak12500 = enable_source(rak12500_bt, "RAK12500_gnss.cpp")
    elif check_line == "RAK13011A":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_A.h")
    elif check_line == "RAK13011B":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_B.h")
    elif check_line == "RAK13011C":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_C.h")
    elif check_line == "RAK13011D":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_D.h")
    elif check_line == "RAK13011E":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_E.h")
    elif check_line == "RAK13011F":
        rak13011 = enable_source(
            rak13011_bt, "RAK13011_switch.cpp", "RAK13011_switch_S_F.h")
    elif check_line == "RAK3172":
        selected_board = rak3172_board
        rak3172 = True
        rak4631 = False
        selected_board = rak3172_board
        rak3172_bt.config(bg="lime")
        rak4631_bt.config(bg="salmon")
    elif check_line == "RAK4731":
        selected_board = rak4631_board
        rak4631 = True
        rak3172 = False
        selected_board = rak4631_board
        rak4631_bt.config(bg="lime")
        rak3172_bt.config(bg="salmon")

    main_window.update_idletasks()

    return


def on_closing():
    # Remove saved config
    if os.path.exists("./.config"):
        os.remove("./.config")
    # Save current config
    f = open('./.config', 'w')
    if rak1901:
        f.write("RAK1901\n")
    if rak1902:
        f.write("RAK1902\n")
    if rak1903:
        f.write("RAK1903\n")
    if rak1904:
        f.write("RAK1904"+rak1904_slot+"\n")
    if rak1905:
        f.write("RAK1905"+rak1905_slot+"\n")
    if rak1906:
        f.write("RAK1906\n")
    if rak1921:
        f.write("RAK1921\n")
    if rak12002:
        f.write("RAK12002\n")
    if rak12003:
        f.write("RAK12003\n")
    if rak12010:
        f.write("RAK12010\n")
    if rak12014:
        f.write("RAK12014"+rak12014_slot+"\n")
    if rak12019:
        f.write("RAK12019\n")
    if rak12027:
        f.write("RAK12027"+rak12027_slot+"\n")
    if rak12037:
        f.write("RAK12037\n")
    if rak12039:
        f.write("RAK12039\n")
    if rak12040:
        f.write("RAK12040\n")
    if rak12047:
        f.write("RAK12047\n")
    if rak12500:
        f.write("RAK12500\n")
    if rak3172:
        f.write("RAK3172\n")
    if rak4631:
        f.write("RAK4631\n")

    f.close()
    time.sleep(1)

    main_window.destroy()


# Main
main_window = tk.Tk()

main_window.title("RUI3-Modular IDE")

# main_window.geometry("800x400")

for column in range(8):
    main_window.grid_columnconfigure(column, weight=1)
for row in range(11):
    main_window.grid_rowconfigure(row, weight=1)

modules_label1 = tk.Label(text="Select required Modules")
modules_label1.grid(row=0, column=0, columnspan=3)
modules_label2 = tk.Label(text="Core")
modules_label2.grid(row=0, column=3)
modules_label3 = tk.Label(text="Actions")
modules_label3.grid(row=3, column=3)

rak1901_bt = tk.Button(text="RAK1901\nT&H", bg="salmon", command=rak1901_cb)
rak1901_bt.grid(row=1, column=0)
rak1902_bt = tk.Button(text="RAK1902\nBaro", bg="salmon", command=rak1902_cb)
rak1902_bt.grid(row=2, column=0)
rak1903_bt = tk.Button(text="RAK1903\nLight", bg="salmon", command=rak1903_cb)
rak1903_bt.grid(row=3, column=0)
rak1904_bt = tk.Button(text="RAK1904\nAcc", bg="salmon", command=rak1904_cb)
rak1904_bt.grid(row=4, column=0)
rak1905_bt = tk.Button(text="RAK1905\n9DOF", bg="salmon", command=rak1905_cb)
rak1905_bt.grid(row=5, column=0)
rak1906_bt = tk.Button(text="RAK1906\nEnv", bg="salmon", command=rak1906_cb)
rak1906_bt.grid(row=6, column=0)
rak1921_bt = tk.Button(text="RAK1921\nOLED", bg="salmon", command=rak1921_cb)
rak1921_bt.grid(row=7, column=0)

rak12002_bt = tk.Button(text="RAK12002\nRTC", bg="salmon", command=rak12002_cb)
rak12002_bt.grid(row=1, column=1)
rak12003_bt = tk.Button(text="RAK12003\nFIR", bg="salmon", command=rak12003_cb)
rak12003_bt.grid(row=2, column=1)
rak12010_bt = tk.Button(text="RAK12010\nLight",
                        bg="salmon", command=rak12010_cb)
rak12010_bt.grid(row=3, column=1)
rak12014_bt = tk.Button(text="RAK12014\nToF", bg="salmon", command=rak12014_cb)
rak12014_bt.grid(row=4, column=1)
rak12019_bt = tk.Button(text="RAK12019\nUV", bg="salmon", command=rak12019_cb)
rak12019_bt.grid(row=5, column=1)
rak12027_bt = tk.Button(text="RAK12027\nQuake",
                        bg="salmon", command=rak12027_cb)
rak12027_bt.grid(row=6, column=1)
rak12037_bt = tk.Button(text="RAK12037\nCO2", bg="salmon", command=rak12037_cb)
rak12037_bt.grid(row=7, column=1)

rak12039_bt = tk.Button(text="RAK12039\nPM", bg="salmon", command=rak12039_cb)
rak12039_bt.grid(row=1, column=2)
rak12040_bt = tk.Button(text="RAK12040\nTemp Arr",
                        bg="salmon", command=rak12040_cb)
rak12040_bt.grid(row=2, column=2)
rak12047_bt = tk.Button(text="RAK12047\nVOC", bg="salmon", command=rak12047_cb)
rak12047_bt.grid(row=3, column=2)
rak12500_bt = tk.Button(text="RAK12500\nGNSS",
                        bg="salmon", command=rak12500_cb)
rak12500_bt.grid(row=4, column=2)
rak13011_bt = tk.Button(text="RAK13011\nSwitch",
                        bg="salmon", command=rak13011_cb)
rak13011_bt.grid(row=5, column=2)

rak3172_bt = tk.Button(text="RAK3172", bg="salmon", command=rak3172_cb)
rak3172_bt.grid(row=1, column=3)
rak4631_bt = tk.Button(text="RAK4631", bg="salmon", command=rak4631_cb)
rak4631_bt.grid(row=2, column=3)

verify_bt = tk.Button(text="Verify", bg="dodgerblue", command=verify_cb)
verify_bt.grid(row=4, column=3)

compile_bt = tk.Button(text="Download", bg="dodgerblue", command=compile_cb)
compile_bt.grid(row=5, column=3)

clean_bt = tk.Button(text="Clean", bg="dodgerblue", command=clean_build_cb)
clean_bt.grid(row=6, column=3)

result_bt = tk.Button(text="Result", bg="dodgerblue")
result_bt.grid(row=7, column=3)

output_field = scrolledtext.ScrolledText(
    main_window, wrap=tk.WORD, width=52, font="TkSmallCaptionFont")
output_field.grid(row=0, column=4, rowspan=12, columnspan=5)

for file_name in listdir("../"):
    if file_name.startswith('RAK'):
        os.remove("../" + file_name)

if platform == "linux" or platform == "linux2":
    arduino_cli_cmd = "./arduino-cli_0.29.0_Linux_64bit/arduino-cli"
elif platform == "darwin":
    arduino_cli_cmd = "./arduino-cli_0.29.0_macOS_64bit/arduino-cli"
elif platform == "win32":
    arduino_cli_cmd = "./arduino-cli_0.27.1_Windows_64bit/arduino-cli.exe"

if not os.path.exists("./.bsp"):
    install_bt = tk.Button(text="INSTALL\nREQUIRED!",
                           bg="salmon", command=check_installation)
    install_bt.grid(row=8, column=3)
    installation_complete = False
else:
    install_bt = tk.Button(text="Refresh\nInstallation!",
                           bg="lime", command=refresh_installation)
    install_bt.grid(row=8, column=3)
    installation_complete = True

port_label = tk.Label(text="Select a port")
port_label.grid(row=9, column=0, columnspan=4)

port_selector_cb = ttk.Combobox(main_window, values=serial_ports(), width=60)
port_selector_cb.grid(row=10, column=0, rowspan=2, columnspan=4)

# assign function to combobox
port_selector_cb.bind('<<ComboboxSelected>>', on_select)

main_window.protocol("WM_DELETE_WINDOW", on_closing)

main_window.after(250, check_config)

main_window.iconbitmap("./rak-blue-dark-whirl.ico")
main_window.mainloop()
