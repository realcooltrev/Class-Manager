import logging

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


def login() -> User:
    username_is_invalid = True
    current_user: User

    while username_is_invalid:
        entered_username = input("Hello! Please enter your username: ")

        current_user = User(entered_username, f"{entered_username}@test.edu", Permissions.STUDENT)
        break

    return current_user

