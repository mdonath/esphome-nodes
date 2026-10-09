"Ni
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