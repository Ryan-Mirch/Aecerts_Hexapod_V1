extends Node

var MainPage = null
var ControlsPage = null
var MenuPage = null
var OffsetsPage = null
var StatsPage = null
var SettingsPage = null
var GaitPage = null

enum PageNames {Main, Controls, Menu, Offsets, Stats, Settings, Gait}
var pageDict = {}

func _ready():
	get_tree().create_timer(0.3).timeout.connect(updateDict)

func updateDict():	
	pageDict[PageNames.Main] = MainPage
	pageDict[PageNames.Controls] = ControlsPage
	pageDict[PageNames.Menu] = MenuPage
	pageDict[PageNames.Offsets] = OffsetsPage
	pageDict[PageNames.Stats] = StatsPage
	pageDict[PageNames.Settings] = SettingsPage
	pageDict[PageNames.Gait] = GaitPage

