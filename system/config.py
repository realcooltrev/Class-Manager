import configparser
from enum import Enum

import psycopg2


class Env(Enum):
    PROD = "prod"
    TEST = "test"


class Config():
    db: any
    environment: Env
    _file_name = "config.ini"

    @classmethod
    def load(cls, environment: Env) -> None:
        """Load the application configuration settings."""
        cls.environment = environment

        config = configparser.ConfigParser()
        
        # Attempt to load the settings from the configuration file
        try:
            with open(f"../{cls._file_name}") as f:
                config.read_file(f)

        # If unable, initialize the file
        except IOError:
            print(f"{cls._file_name} file not found")
            print(f"Running setup for {cls._file_name} file...")
            open(f"../{cls._file_name}", "w").close()
            cls._db_setup(config, environment)

        # Attempt to load the environment-specific database settings
        try:
            cls.db = config[f"db_{environment}"]

        # If unable, walk the user through setting this up
        except configparser.NoSectionError:
            print(f"Configuration for db_{environment} not found")
            print(f"Running config setup for db_{environment}...")
            cls._db_setup(config, f"db_{environment}")

    @classmethod
    def _db_setup(cls, config: configparser.ConfigParser(), environment: Env) -> None:
        """Walk the user through setting up their environment-specific database settings."""
        config["db_{environment}"]["name"] = input("Database name: ")
        config["db_{environment}"]["user"] = input("Database user: ")
        config["db_{environment}"]["password"] = input("Database password: ")
        config["db_{environment}"]["host"] = input("Database host: ")
        config["db_{environment}"]["port"] = input("Database port: ")
        
        with open(f"../{cls._file_name}", "a+") as f:
            config.write(f)
        
        cls.db = config[f"db_{environment}"]
