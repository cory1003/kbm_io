import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QStackedWidget, QVBoxLayout, QHBoxLayout, QLabel, QMenuBar, QLineEdit, QFormLayout, QCheckBox

from PyQt6.QtGui import QColor, QPalette, QAction, QIntValidator, QDoubleValidator, QFont

from script_runner.script_runner import ScriptMenu


class FileMenu(QMenuBar):
    def __init__(self):
        super().__init__()
        button_action1 = QAction( "Your &button2", self)
        button_action1.setStatusTip("This is your button2")
        button_action1.triggered.connect(self.toolbar_button_clicked)
        file_menu = self.addMenu("&File")
        file_menu.addAction(button_action1)

    def toolbar_button_clicked(self, s):
        print("click", s)

    pass

class Color(QWidget):
    def __init__(self, color):
        super().__init__()
        self.setAutoFillBackground(True)

        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        
        self.central_widget = QStackedWidget()
        self.setCentralWidget(self.central_widget)

        layout  = QVBoxLayout()

        login_widget = LoginWidget(self)
        login_widget.button.clicked.connect(self.login)
        layout.addWidget(login_widget)


        second_widget = SecondWidget(self)
        second_widget.button.clicked.connect(self.login)
        layout.addWidget(second_widget)

        script_widget = ScriptMenuSelectBtn()
        script_widget.button.clicked.connect(self.script_menu)
        layout.addWidget(script_widget)


        widget = QWidget()
        widget.setLayout(layout)
        self.central_widget.addWidget(widget)
        self.central_widget.setCurrentWidget(widget)

        self.setMenuBar(FileMenu())


    def toolbar_button_clicked(self, s):
        print("click", s)




    def login(self):
        logged_in_widget = LoggedWidget(self)
        self.central_widget.addWidget(logged_in_widget)
        self.central_widget.setCurrentWidget(logged_in_widget)

    def second(self):
        second_widget = SecondWidget(self)
        self.central_widget.addWidget(second_widget)
        self.setCurrentWidget(second_widget)
    
    def script_menu(self):
        self.script_menu_layout = ScriptMenu(self)
        self.central_widget.addWidget(script_menu_layout)
        self.central_widget.setCurrentWidget(self.script_menu_layout)

    def index(self):
         layout  = QVBoxLayout()






class LoginWidget(QWidget):
    def __init__(self, parent=None):
        super(LoginWidget, self).__init__(parent)
        layout = QHBoxLayout()
        self.button = QPushButton('Login')
        layout.addWidget(self.button)
        self.setLayout(layout)



class SecondWidget(QWidget):
    def __init__(self, parent=None):
        super(SecondWidget, self).__init__(parent)
        layout = QHBoxLayout()
        self.button = QPushButton('Second')
        layout.addWidget(self.button)
        self.setLayout(layout)
        # you might want to do self.button.click.connect(self.parent().login) here


class LoggedWidget(QWidget):
    def __init__(self, parent=None):
        super(LoggedWidget, self).__init__(parent)
        layout = QHBoxLayout()
        self.label = QLabel('logged in!')
        layout.addWidget(self.label)
        self.setLayout(layout)


class ScriptMenuSelectBtn(QWidget):
    def __init__(self, parent=None):
        super().__init__()
        layout = QHBoxLayout()
        self.button = QPushButton('Script Runner')
        layout.addWidget(self.button)
        self.setLayout(layout)





app = QApplication(sys.argv)

window = MainWindow()
window.show()

app.exec()


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