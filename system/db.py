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
        result: str
        query = """
            select username 
                from users
                where username = (%(username)s)"""

        with cls.connection.cursor(cursor_factory=psycopg2.extras.DictCursor) as cursor:
            try:
                cursor.execute(query, {"username", username})
                record = cursor.fetchone()
                return True

            except psycopg2.ProgrammingError as e:
                return False
