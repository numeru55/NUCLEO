import machine
i2c = machine.I2C(sda=machine.Pin('B7'), scl=machine.Pin('B8'))
print(i2c.scan())