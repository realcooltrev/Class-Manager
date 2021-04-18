from io import StringIO
from pathlib import Path

import pytest

from app.config import Config
from app.config import Env


@pytest.fixture
def config(monkeypatch):
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
    # TODO: Need to populate mock config file with data
    Config.load(Env.TEST)
    yield Config
    Config.reset()
    Path(mock_config_filename).unlink(True)


@pytest.fixture
def new_config(monkeypatch):
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
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

