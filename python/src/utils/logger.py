import sys
import time
from datetime import datetime
from colorama import init, Fore, Style

init(autoreset=True)

class Logger:
    LEVELS = {
        "INFO": Fore.CYAN,
        "DEBUG": Fore.BLUE,
        "WARNING": Fore.YELLOW,
        "ERROR": Fore.RED,
        "SUCCESS": Fore.GREEN,
    }
    
    @staticmethod
    def log(level: str, message: str):
        if level not in Logger.LEVELS:
            raise ValueError(f"Invalid log level: {level}")

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        formatted_mssg = (
            f"{Style.BRIGHT}[{timestamp}] {Logger.LEVELS[level]}[{level}] {Style.RESET_ALL}{message}"
        )
        print(formatted_mssg, file=sys.stdout)
    
    @staticmethod
    def info(message: str):
        Logger.log("INFO", message)
        
    @staticmethod
    def debug(message: str):
        Logger.log("DEBUG", message)
    
    @staticmethod
    def warning(message: str):
        Logger.log("WARNING", message)
    
    @staticmethod
    def error(message: str):
        Logger.log("ERROR", message)
    
    @staticmethod
    def success(message: str):
        Logger.log("SUCCESS", message)