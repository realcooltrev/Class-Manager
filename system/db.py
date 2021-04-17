import psycopg2

from . config import Config

class Db():
    connection: any

    @classmethod
    def connect(cls) -> None:
        cls.connection = psycopg2.connect(
            db_name=Config.db["name"],
            user=Config.db["user"],
            password=Config.db["password"],
            host=Config.db["host"],
            port=Config.db["port"]
        )

    @classmethod
    def check_username(cls, username: str) -> bool:
        with cls.connection.cursor() as cursor:
            cursor.execute("")

        return True