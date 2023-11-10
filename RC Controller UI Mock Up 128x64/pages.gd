extends Node

var MainPage = null
var ControlsPage = null
var MenuPage = null
var ServoOffsetsPage = null
var StatsPage = null
var SettingsPage = null

enum PageNames {Main, Controls, Menu, ServoOffsets, Stats, Settings}
var pageDict = {}

func _ready():
	get_tree().create_timer(0.1).timeout.connect(updateDict)

func updateDict():	
	pageDict[PageNames.Main] = MainPage
	pageDict[PageNames.Controls] = ControlsPage
	pageDict[PageNames.Menu] = MenuPage
	pageDict[PageNames.ServoOffsets] = ServoOffsetsPage
	pageDict[PageNames.Stats] = StatsPage
	pageDict[PageNames.Settings] = SettingsPage

