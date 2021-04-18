import atexit
from getpass import getpass
import hashlib
import logging
import os

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
        hashed_pass = hashlib.pbkdf2_hmac(
            hash_name="sha256",
            password=entered_password.encode(),
            salt=os.urandom(),
            iterations=100_000
        )
        try:
            current_user = Sql.authenticate_user(
                entered_username,
                hashed_pass.hex()
            )
            not_authenicated = False
            break

        Exception AuthenticationError:
            print("Username/password is invalid")

    return current_user
