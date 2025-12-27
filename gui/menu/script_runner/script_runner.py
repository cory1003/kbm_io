import sys

from  menu.menu_common2 import *
from multiprocessing import Lock, Process

class ScriptMenu(QWidget):

    name = "Script Menu"

    def __init__(self, parent=None):
        self.run_lock = Lock()
        self.script_thread = None
        app.register_shutdown_function(self.on_exit)
        self.is_running = False

        super(ScriptMenu, self).__init__(parent)
        page_layout = QHBoxLayout()
        btn_layout = QVBoxLayout()
        
        script_config_layout = QVBoxLayout()
       
        page_layout.addLayout(btn_layout)
        page_layout.addStretch()
        page_layout.addLayout(script_config_layout)

        script_config_layout.addLayout(self._generate_script_config_form())

        self.play_btn = QPushButton('Run Script')
        self.play_btn.clicked.connect( self.run_script)
        btn_layout.addWidget(self.play_btn)
        self.load_config_btn = QPushButton('Load Configuration')
        self.load_config_btn.clicked.connect(self.run_script)
        # btn_layout.addWidget(self.load_config_btn)
        combobox1 = QComboBox()
        combobox1.addItems(['Recording 1', 'Recording 2'])
        script_config_layout.addWidget(combobox1)
        script_config_layout.addStretch()
        btn_layout.addStretch()
        self.setLayout(page_layout)

    def _generate_script_config_form(self):

        flo = QFormLayout()

        self.num_iterations_box = QLineEdit()
        self.num_iterations_box.setValidator(QIntValidator())
        self.num_iterations_box.setMaxLength(4)
        self.num_iterations_box.setText("100")
        flo.addRow("Number of Iterations", self.num_iterations_box)

        self.initial_delay_box = QLineEdit()
        self.initial_delay_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        self.initial_delay_box.setText("2")
        flo.addRow("Initial Delay", self.initial_delay_box)

        click_only_box = QCheckBox('')
        click_only_box.stateChanged.connect(self.click_only_checkbox_toggle)
        flo.addRow("Click Only", click_only_box)

        delay_box = QLineEdit()
        delay_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        self.delay_box = delay_box
        self.delay_box.setText('400')
        flo.addRow("Delay Between Actions", delay_box)

        self.deviation_box = QLineEdit()
        self.deviation_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        flo.addRow("Standard Deviation", self.deviation_box)
        self.get_std_dev = self.deviation_box.text
        self.deviation_box.setText("40")

        

        return flo
    def _run_script(self, script = None):
        print("running script")
        print(self.num_iterations_box.text())
        import subprocess
        import time
        sleep_time = self.initial_delay_box.text()
        if len(sleep_time):
            time.sleep(int(sleep_time))
        subprocess.run(["auto-click", '-p', '-i', self.num_iterations_box.text(), '-D', self.initial_delay_box.text(), '-d', self.delay_box.text(), '-S', self.deviation_box.text() ])

        print("end of script.")


        with self.run_lock:
            self.is_running = False
        return

    def run_script(self):
        print(f'DEv: {self.get_std_dev()}')
        with self.run_lock:
            if self.is_running:
                print("already running")
                return
            
        self.is_running = True
        self.script_thread = Process(target=self._run_script)
        self.script_thread.start()
        # if self.is_running:
        #     print("already running")
        #     return
    
        
        return
        # self.is_running = True
        # print("run script")
        # print(self.num_iterations_box.text())
        # import subprocess
        # import time
        # sleep_time = self.initial_delay_box.text()
        # if len(sleep_time):
        #     time.sleep(int(sleep_time))
        # subprocess.run(["auto-click", '-p', '-i', self.num_iterations_box.text(), '-D', self.initial_delay_box.text(), '-d', self.delay_box.text(), '-S', self.deviation_box.text() ])
 
        # self.is_running = False
        # print("end of script.")
        # auto-click -S .1 -p -d 1 -i 600 -D 1


    def click_only_checkbox_toggle(self, state):
        print("Click Only!")


    def on_exit(self):
        
        print("on_exit")
        with self.run_lock:
            print("killing")
            if self.is_running:
                if self.script_thread._popen:
                    self.script_thread.terminate()  
                print("terminated")
            