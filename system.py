import logging
from os import environ

import psycopg2

from models import Permissions
from models import User

class Config():
    db: psycopg2.connection

    def load(self) -> None:
        logging.basicConfig(
            filename="sis.log",
            encoding="utf-8",
            level=logging.INFO
        )
        logging.info("System starting up...")
        logging.info("Connecting to database...")
        self.db = psycopg2.connect(
            db_name=environ["PGDATABASE"],
            user=environ["PGUSER"],
            password=environ["PGPASSWORD"],
            host=environ["PGHOST"],
            port=environ["PGPORT"]
        )
        logging.info("Connected to database successfully")


def startup() -> None:
    Config.load()

def login() -> User:
    username_is_invalid = True
    current_user: User

    while username_is_invalid:
        entered_username = input("Hello! Please enter your username: ")
        username_is_invalid = False
        current_user = User(entered_username, f"{entered_username}@test.edu", Permissions.STUDENT)
        break

    return current_user

