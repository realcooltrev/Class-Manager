class Student(User):
    def __init__(self, grades: list[Assignment]) -> None:
        super().__init__("User")
        self.grades: grades