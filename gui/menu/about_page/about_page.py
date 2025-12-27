import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox, QComboBox

from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont

from app import app


class AboutPage(QWidget):
    name = "About Page"
    def __init__(self, parent=None):
        super(type(self), self).__init__(parent)
        page_layout = QHBoxLayout()
        self.setLayout(page_layout)
        #left, top, right, botto
        page_layout.setContentsMargins(30, 10, 30, 10)
        about_text='''This is a simple mouse and keyboard recorder and playback device as well as a keyboard and mouse macro generator.

This is a tool intended to assist in tedious or repetive mouse and keyboard tasks, either in a video game or a desktop application.




Current Support:

Linux: Yes
Windows: Comming Soon
Mac: N/A


Copyright: SoftwareDougXXX 
'''
        about_label = QLabel(about_text)
        about_label.setWordWrap(True)
        page_layout.addWidget(about_label)
__all__ = ["AboutPage"]