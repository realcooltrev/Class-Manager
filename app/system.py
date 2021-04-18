import argparse
import atexit
from getpass import getpass
import hashlib
import logging
import os
import sys

from app.db import Db
from app.db import Sql
from app.exceptions import AuthenticationError
from app.config import Config
from app.config import Env
from app.models import Permissions
from app.models import User


def get_cli_args() -> argparse.Namespace:
    """Get the application's command line arguments."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-e",
        "--environment",
        required=True,
        help="The environment that this application is running in",
        choices=[
            f"{Env.PROD}",
            f"{Env.TEST}",
        ]
    )
    return parser.parse_args()


def startup() -> None:
    """Setup everything needed for the application to run."""
    args = get_cli_args()
    logging.basicConfig(
        filename="sis.log",
        encoding="utf-8",
        level=logging.INFO
    )

    logging.info("System starting up...")
    logging.info("Loading system configuration...")
    Config.load(args.environment)

    logging.info("Sytem configuration loaded successfully")
    logging.info("Connecting to data source...")
    Db.connect()

    logging.info("Data source connection established successfully")


@atexit.register
def shutdown() -> None:
    """Perform cleanup needed prior to application shutdown."""
    Db.connection.close()
    sys.exit(0)


def login() -> User:
    """Get a user's credentials and authenticate them against the database."""
    current_user: User
    not_authenicated: True

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

        except AuthenticationError:
            print("Username/password is invalid")

    return current_user
