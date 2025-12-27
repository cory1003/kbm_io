
menus = {}
home_page_index = {}
import signal,sys
from collections import deque

def set_page( page ):
    print("here")
    # main_window.set_page( page )

def signal_handler(signum, frame):
    print(f"Received signal {signum}. Initiating graceful shutdown...")
    app.exit()
    # Add your shutdown logic here (e.g., close connections, save state)
    sys.exit(0) # Exit the application after cleanup

class MainApplication():
    main_window = None
    def __init__(self, window=None):
        
        self.main_window = window
        self.shutdown_functions = deque()
        pass
    def set_main_window(self, window):
        self.main_window = window
    def set_page( self, page ):
        
        print("here")
        # main_window.set_page( page )

    def init_signals(self):
        signal.signal(signal.SIGINT, self.signal_handler)
        signal.signal(signal.SIGTERM, self.signal_handler)


    def register_shutdown_function(self, function ):
        self.shutdown_functions.append(function)

    def signal_handler(self, signum,frame):
        print(f"Received signal {signum}. Initiating graceful shutdown...")
        self.exit()
    def exit(self):
        
        while self.shutdown_functions:
            func = self.shutdown_functions.pop()
            func()
        pass
        sys.exit(0) # Exit the application after cleanup


app =  MainApplication()




# signal.signal(signal.SIGINT, signal_handler)
# signal.signal(signal.SIGTERM, signal_handler)