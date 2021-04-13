import logging

from models import User
import system

if __name__ == "__main__":
    logging.basicConfig(filename="sis.log", encoding="utf-8", level=logging.INFO)
    current_user = system.login()