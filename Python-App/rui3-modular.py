import tkinter as tk
from tkinter import scrolledtext
import tkinter.ttk as ttk
from tkinter import messagebox
import shutil
import os
from os import listdir
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
rak1905 = False
rak1906 = False
rak1921 = False
rak12002 = False
rak12003 = False
rak12010 = False
rak12014 = False
rak12019 = False
rak12027 = False
rak12037 = False
rak12039 = False
rak12040 = False
rak12047 = False
rak12500 = False
rak13011 = False


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


def handle_source(module, module_bt, source_name):
    print(source_name)
    if (module == True):
        module = False
        module_bt.config(bg="salmon")
        os.remove("../"+source_name)
        return False
    else:
        module = True
        module_bt.config(bg="lime")
        shutil.copy("../module-files/"+source_name, "../")
        return True
    return

    return


def rak1901_cb():
    global rak1901
    global rak1901_bt
    rak1901 = handle_source(rak1901, rak1901_bt, "rak1901_temp.cpp")
    return


def rak1902_cb():
    global rak1902
    global rak1902_bt
    rak1902 = handle_source(rak1902, rak1902_bt, "rak1902_press.cpp")
    return


def rak1903_cb():
    global rak1903
    global rak1903_bt
    rak1903 = handle_source(rak1903, rak1903_bt, "rak1903_light.cpp")
    return


def rak1904_cb():
    global rak1904
    global rak1904_bt
    rak1904 = handle_source(rak1904, rak1904_bt, "rak1904_acc.cpp")
    return


def rak1905_cb():
    global rak1905
    global rak1905_bt
    rak1905 = handle_source(rak1905, rak1905_bt, "rak1905_9dof.cpp")
    return


def rak1906_cb():
    global rak1906
    global rak1906_bt
    rak1906 = handle_source(rak1906, rak1906_bt, "rak1906_env.cpp")
    return


def rak1921_cb():
    global rak1921
    global rak1921_bt
    rak1921 = handle_source(rak1921, rak1921_bt, "rak1921_display.cpp")
    return


def rak12002_cb():
    global rak12002
    global rak12002_bt
    rak12002 = handle_source(rak12002, rak12002_bt, "rak2002_rtc.cpp")
    return


def rak12002_cb():
    global rak12002
    global rak12002_bt
    rak12002 = handle_source(rak12002, rak12002_bt, "rak12002_rtc.cpp")
    return


def rak12003_cb():
    global rak12003
    global rak12003_bt
    rak12003 = handle_source(rak12003, rak12003_bt, "rak12003_fir.cpp")
    return


def rak12010_cb():
    global rak12010
    global rak12010_bt
    rak12010 = handle_source(rak12010, rak12010_bt, "rak12010_light.cpp")
    return


def rak12014_cb():
    global rak12014
    global rak12014_bt
    rak12014 = handle_source(rak12014, rak12014_bt, "rak12014_tof.cpp")
    return


def rak12019_cb():
    global rak12019
    global rak12019_bt
    rak12019 = handle_source(rak12019, rak12019_bt, "rak12019_uv.cpp")
    return


def rak12027_cb():
    global rak12027
    global rak12027_bt
    rak12027 = handle_source(rak12027, rak12027, "rak12027_seismic.cpp")
    return


def rak12037_cb():
    global rak12037
    global rak12037_bt
    rak12037 = handle_source(rak12037, rak12037_bt, "rak12037_co2.cpp")
    return


def rak12039_cb():
    global rak12039
    global rak12039_bt
    rak12039 = handle_source(rak12039, rak12039_bt, "rak12039_pm.cpp")
    return


def rak12040_cb():
    global rak12040
    global rak12040_bt
    rak12040 = handle_source(rak12040, rak12040_bt, "rak12040__temp_arr.cpp")
    return


def rak12047_cb():
    global rak12047
    global rak12047_bt
    rak12047 = handle_source(rak12047, rak12047_bt, "rak12047_voc.cpp")
    return


def rak12500_cb():
    global rak12500
    global rak12500_bt
    rak12500 = handle_source(rak12500, rak12500_bt, "rak12500_gnss.cpp")
    return


def rak13011_cb():
    global rak13011
    global rak13011_bt
    rak13011 = handle_source(rak13011, rak13011_bt, "rak13011_switch.cpp")
    return


def rak3172_cb():
    global rak3172_board
    global selected_board
    global rak3172_bt
    global rak4631_bt
    selected_board = rak3172_board
    rak3172 = True
    rak4631 = False
    rak3172_bt.config(bg="lime")
    rak4631_bt.config(bg="salmon")
    return


def rak4631_cb():
    global rak3172_board
    global selected_board
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
                            universal_newlines=True)

    while True:
        line = proc.stdout.read()
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

    print("Finished "+command)
    return proc.returncode


def verify_cb():
    global selected_board

    if (not installation_complete):
        messagebox.showerror("ERROR", "Installation required first")
        return
    if (selected_board == ""):
        messagebox.showerror("ERROR", "Select a board first")
        return

    compile_command = arduino_cli_cmd + " compile -b " + selected_board + \
        " --output-dir ../Build --build-cache-path ../Build --no-color --library ../libraries ../RUI3-Modular.ino"
    headline = "Verify, this can take some time, be patient"
    return_code = ext_app_to_log(compile_command, headline, True)

    if (return_code == 0):
        result_bt.config(bg="lime", text="SUCCESS")
    else:
        result_bt.config(bg="salmon", text="FAIL")

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

    compile_command = arduino_cli_cmd + " compile -b " + selected_board + \
        " --output-dir ../Build --build-cache-path ../Build --upload -p " + \
        upload_port + " --no-color --library ../libraries ../RUI3-Modular.ino"

    headline = "Download, this can take some time, be patient"
    return_code = ext_app_to_log(compile_command, headline, True)

    if (return_code == 0):
        result_bt.config(bg="lime", text="SUCCESS")
    else:
        result_bt.config(bg="salmon", text="FAIL")

    return


def clean_build_cb():
    os.remove("../Build")
    return


def refresh_installation():
    compile_command = arduino_cli_cmd + " config delete board_manager.additional_urls"
    headline = "Cleaning up additional BSP URL's"
    return_code1 = ext_app_to_log(compile_command, headline, False)
    time.sleep(10)

    compile_command = arduino_cli_cmd + " config add board_manager.additional_urls https://raw.githubusercontent.com/beegee-tokyo/test/main/beegee-patch-rui3.json"
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

    if (return_code1 == 0) and (return_code2 == 0) and (return_code3 == 0) and (return_code4 == 0):
        result_bt.config(bg="lime", text="SUCCESS")
        with open('./.bsp', 'w') as f:
            f.write('Installation success!')
            f.close()
        installation_complete = True
    else:
        result_bt.config(bg="salmon", text="FAIL")

    return return_code1+return_code2+return_code3+return_code4


def check_installation():
    result = False
    if os.path.exists("./.bsp"):
        result = True
    else:
        if (refresh_installation() == 0):
            install_bt.destroy()
    return


# Main
main_window = tk.Tk()

main_window.title("RUI3-Modular IDE")

main_window.geometry("800x420")

for column in range(100):
    main_window.grid_columnconfigure(column, weight=1)
for row in range(100):
    main_window.grid_rowconfigure(row, weight=1)

modules_label1 = tk.Label(text="Select")
modules_label1.grid(row=0, column=0)
modules_label2 = tk.Label(text="required")
modules_label2.grid(row=0, column=1)
modules_label2 = tk.Label(text="Modules")
modules_label2.grid(row=0, column=2)
modules_label3 = tk.Label(text="	   ")
modules_label3.grid(row=0, column=3)
modules_label4 = tk.Label(text="Core")
modules_label4.grid(row=0, column=4)

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
rak12040_bt = tk.Button(text="RAK12040\nTemp[]",
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
rak3172_bt.grid(row=1, column=4)
rak4631_bt = tk.Button(text="RAK4631", bg="salmon", command=rak4631_cb)
rak4631_bt.grid(row=2, column=4)

verify_bt = tk.Button(text="Verify", bg="dodgerblue", command=verify_cb)
verify_bt.grid(row=4, column=4)

compile_bt = tk.Button(text="Download", bg="dodgerblue", command=compile_cb)
compile_bt.grid(row=5, column=4)

clean_bt = tk.Button(text="Clean", bg="dodgerblue", command=clean_build_cb)
clean_bt.grid(row=6, column=4)

result_bt = tk.Button(text="Result", bg="dodgerblue")
result_bt.grid(row=7, column=4)

output_field = scrolledtext.ScrolledText(main_window, wrap=tk.WORD, width=52)
output_field.place(x=360, y=0)

for file_name in listdir("../"):
    if file_name.startswith('rak1'):
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
port_label.place(x=0, y=380)

port_selector_cb = ttk.Combobox(main_window, values=serial_ports(), width=45)
port_selector_cb.place(x=0, y=400)

# assign function to combobox
port_selector_cb.bind('<<ComboboxSelected>>', on_select)

main_window.iconbitmap("./rak-blue-dark-whirl.ico")
main_window.mainloop()
