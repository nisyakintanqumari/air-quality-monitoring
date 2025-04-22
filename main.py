print("Welcome to Home Security System")
pin = "1234"

entered_pin = input("Enter PIN: ")

if entered_pin == pin:
    print("Door unlocked")
else:
    print("Intruder alert! Taking photo...")
