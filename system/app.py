import atexit
from getpass import getpass
import logging

from . db import Db
from . db import Sql
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
    not_authenicated = True
    current_user: User

    while not_authenicated:
        entered_username = input("Username: ")
        entered_password = getpass("Password: ")

        try:
            current_user = Sql.authenticate_user(
                entered_username,
                entered_password
            )
            not_authenicated = False
            break

        Exception AuthenticationError:
            print("Username/password is invalid")

    return current_user
