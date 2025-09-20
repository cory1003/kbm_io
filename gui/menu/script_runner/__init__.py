from .script_runner import ScriptMenu
from app import app, menus

script_runner_menu = ScriptMenu
menus[ScriptMenu.name]= script_runner_menu