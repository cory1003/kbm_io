
menus = {}
home_page_index = {}



def set_page( page ):
    print("here")
    main_window.set_page( page )



class MainApplication():
    main_window = None
    def __init__(self, window=None):
        self.main_window = window
        pass
    def set_main_window(self, window):
        self.main_window = window
    def set_page( self, page ):
        
        print("here")
        main_window.set_page( page )



app =  MainApplication()