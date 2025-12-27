from menu.menu_common2 import *



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
        
    def set_page(self):
        print("he")
        app.main_window.set_page(self.menu)