import sys
from app import app
from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox
from PyQt6 import QtGui
from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont

from menu.script_runner.script_runner import ScriptMenu
from menu.macro.macro import MacroMenu
from menu import *
# from app.home_page import HomePage

class FileMenu(QMenuBar):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        home_page_btn = QAction( "&Home Page", self)
        home_page_btn.setStatusTip("This is your button2")
        home_page_btn.triggered.connect(self.toolbar_button_clicked)
        file_menu = self.addMenu("&File")
        file_menu.addAction(home_page_btn)

        log_btn = QAction( "&Logs", self)
        log_btn.setStatusTip("View Log History")
        log_btn.triggered.connect(self.toolbar_button_clicked)

        file_menu.addAction(log_btn)


    def toolbar_button_clicked(self, s):
        print("click", s, "s")
        self.main_window.go_to_home_page()

    pass

class Color(QWidget):
    def __init__(self, color):
        super().__init__()
        self.setAutoFillBackground(True)

        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)

class MainWindow(QMainWindow):

    home_page_menu_btns = [ RecordMenu, ScriptMenu, MacroMenu, AboutPage ]

    def __init__(self, parent=None, icon="'/home/double/projects/kbm_io/gui/not-available-circle.ico'"):
        super(MainWindow, self).__init__(parent)
        self.resize(600, 500) 
        self.setWindowTitle("Auto-Clicker")
        self.setWindowIcon( QtGui.QIcon('/home/double/projects/kbm_io/gui/not-available-circle.ico') )
        self.central_widget = QStackedWidget()
        self.setCentralWidget(self.central_widget)
    
        self.menu_list = {}

        layout  = QVBoxLayout()
        layout.addStretch()
 
        for menu in type(self).home_page_menu_btns:
            layout.addWidget( AppMenuPageSelectBtn(menu=menu) )

        layout.addStretch()
        widget = QWidget()
        widget.setLayout(layout)
        self.home_page = widget

        # self.home_page = HomePage(self)
        self.central_widget.addWidget(self.home_page)
        self.central_widget.setCurrentWidget(self.home_page)

        self.setMenuBar(FileMenu(self))

        
    def record_menu(self):
        pass

    def go_to_home_page(self):
        self.central_widget.setCurrentWidget(self.home_page)

    def set_page(self, menu ):
        if menu.name in self.menu_list:
            print("has already")
        else: 
            print("not yet")
            self.menu_list[menu.name] = menu()
            self.central_widget.addWidget(self.menu_list[menu.name])
        self.central_widget.setCurrentWidget(self.menu_list[menu.name])

    def toolbar_button_clicked(self, s):
        print("click", s)

    def index(self):
         layout  = QVBoxLayout()


class AppMenuPageSelectBtn(QWidget):
    def __init__(self, menu = None):
        super().__init__()
        self.menu = menu
        self.name = menu.name

        layout = QHBoxLayout()
        self.button = QPushButton(self.name)
        layout.addWidget(self.button)
        self.setLayout(layout)
        self.button.clicked.connect(self.set_page)
        
        self.button.setFixedWidth( 200 )
    def set_page(self):
        print("he")
        app.main_window.set_page(self.menu)


if __name__ == "__main__":
    app_q = QApplication(sys.argv)
    window = MainWindow()
    app.set_main_window(window)
    window.show()
    import signal
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    app_q.exec()

# class MainWindow(QMainWindow):

#     def __init__(self):
#         super().__init__()

#         self.setWindowTitle("My App")

#         layout1 = QHBoxLayout()
#         layout2 = QVBoxLayout()
#         layout3 = QVBoxLayout()
#         layout1.setContentsMargins(0,0,0,0)
#         layout1.setSpacing(20)

#         layout2.addWidget(Color('red'))
#         layout2.addWidget(Color('yellow'))
#         layout2.addWidget(Color('purple'))

#         layout1.addLayout( layout2 )

#         layout1.addWidget(Color('green'))

#         layout3.addWidget(Color('red'))
#         layout3.addWidget(Color('purple'))

#         layout1.addLayout( layout3 )

#         widget = QWidget()
#         widget.setLayout(layout1)
#         self.setCentralWidget(widget)