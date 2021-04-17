import atexit
import logging

from . db import Db
from . config import Config
from . models import Permissions
from . models import User

def startup() -> None:
    logging.basicConfig(
        filename="sis.log",
        encoding="utf-8",
        level=logging.INFO
    )
    logging.info("System starting up...")
    logging.info("Loading system configuration...")
    Config.load()
    logging.info("Sytem configuration loaded successfully")
    logging.info("Connecting to data source...")
    Db.connect()
    logging.info("Data source connection established successfully")


@atexit.register
def shutdown() -> None:
    Db.connection.close()

def login() -> User:
    username_is_invalid = True
    current_user: User

    while username_is_invalid:
        entered_username = input("Hello! Please enter your username: ")

        current_user = User(entered_username, f"{entered_username}@test.edu", Permissions.STUDENT)
        break

    return current_user

