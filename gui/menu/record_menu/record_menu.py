import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox, QComboBox

from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont

from app import app



class RecordMenu(QWidget):
    name = "Record Menu"
    def __init__(self, parent=None):
        super(type(self), self).__init__(parent)


        
        page_layout = QHBoxLayout()
        btn_layout = QVBoxLayout()
        script_config_layout = QVBoxLayout()

        
        
        page_layout.addLayout(btn_layout)
        page_layout.addLayout(script_config_layout)

        # script_config_layout.addLayout(self._generate_script_config_form())

    
        self.play_btn = QPushButton('Record')
        self.play_btn.clicked.connect(self.record)
        btn_layout.addWidget(self.play_btn)
        self.setLayout(page_layout)
      

        self.script_box = QLineEdit()
        flo = QFormLayout()
        self.database_select = QComboBox()
        self.database_select.addItems(['Game 1', 'Recording 2'])
        flo.addRow("Database", self.database_select)
        flo.addRow("Script Name", self.script_box)
        script_config_layout.addLayout(flo)
        btn_layout.addStretch()
    def _script_form(self):

        flo = QFormLayout()
        click_only_box = QCheckBox('')
        click_only_box.stateChanged.connect(self.click_only_checkbox_toggle)
        flo.addRow("Click Only", click_only_box)

        return flo

    def record(self):
        print("Record Script")

    def click_only_checkbox_toggle(self, state):
        print("Click Only!")