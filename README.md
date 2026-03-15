# Firmware voor eigen devices

## Installeren en updaten van ESPHOME

Installeer tenminste Python 3.9:

```shell
sudo apt-get install python3.10 # of hoger
```

Maak een venv met de geïnstalleerde versie (de standaard Python kan een lagere zijn), en activeer deze:
```shell
python3 -m venv venv
. venv/bin/activate
```

Installeer `esphome`:
```shell
pip install esphome
```

Later kun je updaten met:
```shell
pip install esphome --upgrade   # (of -U)
```
# Te installeren extra's:
De nodes `klok[1-n]` doen iets met lettertypes en hebben daarvoor de library `pillow` nodig:
```shell
pip install pillow==11.3.0
```

Of alle benodigde libraries in één keer:
```shell
pip install -r requirements.txt
```

# Node builden en uploaden
Bouwen en gelijk uploaden via `run`:
```shell
esphome run klok1.yaml
```