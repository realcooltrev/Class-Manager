import configparser
from pathlib import Path

import pytest

from app.config import Config
from app.config import Env


@pytest.fixture
def config():
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
    Path(mock_config_filename).touch()

    config = configparser.ConfigParser()
    config.read_dict(
        {
            f"db_{Env.TEST}": {
                "name": "test_database",
                "user": "test_user",
                "password": "test_password",
                "host": "test_host",
                "port": "test_port",
            }
        }
    )

    with open(mock_config_filename, "w") as f:
        config.write(f)

    Config.load(Env.TEST, mock_config_filename)
    yield Config
    Config.reset()
    Path(mock_config_filename).unlink(True)


@pytest.fixture
def new_config(monkeypatch):
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)

    # So, this only actually overrides input calls once (the test_port one)
    # Need to figure out a better solution so that this can be tested
    # Maybe an event hook?
    monkeypatch.setattr("builtins.input", lambda *args: "test_database")
    monkeypatch.setattr("builtins.input", lambda *args: "test_user")
    monkeypatch.setattr("builtins.input", lambda *args: "test_password")
    monkeypatch.setattr("builtins.input", lambda *args: "test_host")
    monkeypatch.setattr("builtins.input", lambda *args: "test_port")

    Config.load(Env.TEST, mock_config_filename)
    yield Config
    Config.reset()
    Path(mock_config_filename).unlink(True)


def test_load(config):
    expected_configs = [
        "test_database",
        "test_user",
        "test_password",
        "test_host",
        "test_port",
    ]
    assert sorted(expected_configs) == sorted(list(config.db.values()))


def test_no_config_file(new_config):
    expected_configs = [
        "test_database",
        "test_user",
        "test_password",
        "test_host",
        "test_port",
    ]
    print(list(new_config.db.values()))
    assert sorted(expected_configs) == sorted(list(new_config.db.values()))

