import psycopg2

from . config import Config
from . models import User
from . exceptions import AuthenticationError


class Db():
    connection: any

    @classmethod
    def connect(cls) -> None:
        """Create a static connection to the SIS database."""
        cls.connection = psycopg2.connect(
            db_name=Config.db["name"],
            user=Config.db["user"],
            password=Config.db["password"],
            host=Config.db["host"],
            port=Config.db["port"]
        )


class Sql():
    @staticmethod
    def authenticate_user(username: str, password: str) -> User:
        """Check for a user matching the given username and password."""
        query = (
            "select permissions"
            "   from users"
            "   where username = (%(username)s)"
            "     and password = (%(password)s)"
        )

        with Db.connection.cursor() as cursor:
            try:
                cursor.execute(
                    query,
                    {
                        "username": username,
                        "password": password,
                    }
                )
                permissions, = cursor.fetchone()
                return User(username, permissions)

            except psycopg2.ProgrammingError:
                raise AuthenticationError
