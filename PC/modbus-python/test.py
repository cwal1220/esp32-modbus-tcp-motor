from pymodbus.client import ModbusTcpClient
from pymodbus.transaction import *

client = ModbusTcpClient('192.168.0.100', 502)
# client = ModbusTcpClient('127.0.0.1', 502)
# client.write_coil(100, True)
# result = client.read_coils(100, 16)

while(True):
    result = client.read_input_registers(100)
    # result = client.read_holding_registers(100)
    print(result.registers)
    
# print(result.registers)