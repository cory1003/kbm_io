from menu.menu_common import *

class ScriptMenu(QWidget):

    name = "Script Menu"

    def __init__(self, parent=None):

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
        self.play_btn.clicked.connect(self.run_script)
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
        flo.addRow("Number of Iterations", self.num_iterations_box)

        self.initial_delay_box = QLineEdit()
        self.initial_delay_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        flo.addRow("Initial Delay", self.initial_delay_box)

        click_only_box = QCheckBox('')
        click_only_box.stateChanged.connect(self.click_only_checkbox_toggle)
        flo.addRow("Click Only", click_only_box)

        delay_box = QLineEdit()
        delay_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        flo.addRow("Delay Between Actions", delay_box)

        deviation_box = QLineEdit()
        deviation_box.setValidator(QDoubleValidator(0.0 ,2e9,15))
        flo.addRow("Standard Deviation", deviation_box)
        self.get_std_dev = deviation_box.text

        

        return flo

    def run_script(self):
        print(f'DEv: {self.get_std_dev()}')
        if self.is_running:
            print("already running")
            return
        
        self.is_running = True
        print("run script")
        print(self.num_iterations_box.text())
        import subprocess
        import time
        sleep_time = self.initial_delay_box.text()
        if len(sleep_time):
            time.sleep(int(sleep_time))
        subprocess.run(["auto-click", '-p', '-i', '21', '-D', '1', 'd' '1'])

        


        self.is_running = False
        print("end of script.")
        # auto-click -S .1 -p -d 1 -i 600 -D 1


    def click_only_checkbox_toggle(self, state):
        print("Click Only!")

