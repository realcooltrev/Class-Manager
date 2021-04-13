import psycopg2

from models import Permissions
from models import User

class Config():
    _db_name = "test"
    _db_user = "postgres"
    _db_secret = ""
    db_url = f"dbname={_db_name} user={_db_user} secret={_db_secret}"


def login() -> User:
    username_is_invalid = True
    current_user: User

    while username_is_invalid:
        entered_username = input("Hello! Please enter your username: ")
        username_is_invalid = False
        conn = psycopg2.connect(Config.db_url)
        current_user = User(entered_username, f"{entered_username}@test.edu", Permissions.STUDENT)
        break

    return current_user

