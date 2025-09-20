import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox

from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont



class MacroMenu(QWidget):

    name = "Macros"

    def __init__(self, parent=None):

        self.is_running = False

        super(MacroMenu, self).__init__(parent)
        page_layout = QHBoxLayout()
        btn_layout = QVBoxLayout()
        
        script_config_layout = QVBoxLayout()
       
        page_layout.addLayout(btn_layout)
        page_layout.addStretch()
        page_layout.addLayout(script_config_layout)

        script_config_layout.addLayout(self._generate_script_config_form())

        self.play_btn = QPushButton('Create Macro')
        self.play_btn.clicked.connect(lambda: self.set_page(42))
        btn_layout.addWidget(self.play_btn)


        self.enable_macro = QPushButton('Enable Macro')
        self.enable_macro.clicked.connect(lambda: self.set_page(42))
        btn_layout.addWidget(self.enable_macro)
        # btn_layout.addWidget(self.load_config_btn)


        btn_layout.addStretch()
        self.setLayout(page_layout)

    def _generate_script_config_form(self):

        flo = QFormLayout()
        click_only_box = QCheckBox('')
        click_only_box.stateChanged.connect(self.click_only_checkbox_toggle)
        flo.addRow("Click Only", click_only_box)
        return flo

    def add_macro(self):
        if self.is_running:
            print("already running")
            return
        print("end of script.")
        # auto-click -S .1 -p -d 1 -i 600 -D 1

    def set_page( self, page ):
        print(page)
    def click_only_checkbox_toggle(self, state):
        print("Click Only!")

