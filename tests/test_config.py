import configparser
from io import StringIO
from pathlib import Path

import pytest

from app.config import Config
from app.config import Env


@pytest.fixture
def config(monkeypatch):
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
    Path(mock_config_filename).touch()
    config = configparser.ConfigParser()
    config.add_section(f"db_{Env.TEST}")
    config.set(f"db_{Env.TEST}", "name", "test_database")
    config.set(f"db_{Env.TEST}", "user", "test_user")
    config.set(f"db_{Env.TEST}", "password", "test_password")
    config.set(f"db_{Env.TEST}", "host", "test_host")
    config.set(f"db_{Env.TEST}", "port", "test_port")

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
    # TODO: stdin isn't working after the first string is sent
    monkeypatch.setattr("sys.stdin", StringIO("test_database"))
    monkeypatch.setattr("sys.stdin", StringIO("test_user"))
    monkeypatch.setattr("sys.stdin", StringIO("test_password"))
    monkeypatch.setattr("sys.stdin", StringIO("test_host"))
    monkeypatch.setattr("sys.stdin", StringIO("test_port"))
    Config.load(Env.TEST, mock_config_filename)
    yield Config
    Config.reset()
    Path(mock_config_filename).unlink(True)


def test_load(config):
    expected_configs = [
        "name",
        "host",
        "password"
        "port",
        "user",
    ]
    assert expected_configs in config.db


def test_no_config_file(new_config):
    assert new_config.db is not None

