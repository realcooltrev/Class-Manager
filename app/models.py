from enum import Enum


class Assignment:
    def __init__(self, name: str, score: int) -> None:
        self.name = name
        self.score = score


class Permissions(Enum):
    FACULTY = "F"
    STAFF = "A"
    STUDENT = "S"


class User:
    def __init__(self, username: str, permissions: Permissions) -> None:
        self.username = username
        self.permissions = permissions

    def check_grades(self) -> list[Assignment]:
        if self.permissions == Permissions.STUDENT:
            pass
        pass
