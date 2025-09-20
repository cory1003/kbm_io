import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox

from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont

from app import app

class AppMenuPage(QWidget):
    def __init__(self, app=None, btn_txt="default"):
        super().__init__()
        self.name = btn_txt
        self.app =app 
        layout = QHBoxLayout()
        self.button = QPushButton(btn_txt)
        layout.addWidget(self.button)
        self.setLayout(layout)
        self.button.clicked.connect(self.set_page)
        
    def set_page(self):
        return self.name

class MenuSelectBtn(QWidget):
    def __init__(self, parent=None, btn_txt="default"):
        super().__init__(parent,btn_txt)
        
    def __init__(self, parent=None, btn_txt="default"):
        super().__init__()
        layout = QHBoxLayout()
        self.button = QPushButton(btn_txt)
        layout.addWidget(self.button)
        self.setLayout(layout)

class ScriptMenuSelectBtn(AppMenuPage):
    def __init__(self, app=None, btn_txt="Script Runner"):
        super().__init__(app=app, btn_txt=btn_txt)

    def set_page(self):
        print("sdf")
        print(type(self.app))
        self.app.set_page(ScriptMenu.name)

    def get_page(self):
        return ScriptMenu.name

class HomePage(QWidget):
    def __init__(self, callback):
        self.callback_fun = callback
        self.app = app
        super().__init__()
        layout  = QVBoxLayout()
        layout.addStretch()
        # record_widget = MenuSelectBtn(self, "New Recording")
        # record_widget.button.clicked.connect(self.record_menu)
        # layout.addWidget(record_widget)
        script_widget = ScriptMenuSelectBtn(self.app)
        layout.addWidget(script_widget)
        layout.addStretch()
        self.setLayout(layout)

