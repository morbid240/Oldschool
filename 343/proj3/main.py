import pymongo
from datetime import datetime

# Set up a connection to the MongoDB server
client = pymongo.MongoClient("mongodb://localhost:27017/")

# Get a reference to the "girlscouts" database
db = client["Project3"]

# Get references to the "troops", "scouts", and "adults" collections
troop = db["troop"]
scout = db["scout"]
adult = db["adult"]

def print_troop_summary(troop):
    """Prints a summary of a given troop, including its number, founding date, community, and members."""
    print(f"\nTroop Number: {troop['_id']}")
    founding_date_str = troop['founding_date'].strftime('%B %d, %Y')
    print(f"Founding Date: {founding_date_str}")
    print(f"Community: {troop['community']}")
    print("\nScouts:")
    for scout in troop['scouts']:
        birthdate_str = scout['birthday'].strftime('%B %d, %Y')
        print(f"Name: {scout['firstname']} {scout['lastname']}")
        print(f"Birthday: {birthdate_str}")
        print(f"Grade: {scout['gradelevel']}")
        print("")
    print("\nAdult Volunteers:")
    for adult in troop['volunteers']:
        print(f"{adult['name']} ({adult['roles'][0]['position']})")

def print_scout_detail(scout):
    """Prints a detailed view of a given scout, including their troop, rank, and cookie sales."""
    print(f"\nScout: {scout['firstname']} {scout['lastname']}")
    print(f"Troop Number: {scout['troopnumber']}")
    print(f"Rank: {scout['rank']}")
    print("Cookie Sales:")
    for sale in scout['sales']:
        print(f"{sale['year']} - {sale['total']} boxes")

def troop_lookup():
    """Prompts the user for a troop number and retrieves and prints the summary for that troop."""
    troop_id = input("Enter a troop number: ")
    # define the query using the user input for troop id
    query = {"_id": int(troop_id)}
    # execute the query and retrieve the troop data
    troop_data = troop.find_one(query)
    if troop_data:
        print_troop_summary(troop_data)
    else:
        print(f"No troop found with number {troop_id}")


def sales_report():
    troop_id = input("Enter a troop number: ")
    # Convert the troop_id to an integer
    troop_id = int(troop_id)
    pipeline = [
        {
            '$match': {'_id': troop_id}
        },
        {
            '$unwind': '$scouts'
        },
        {
            '$unwind': '$scouts.allotments'
        },
        {
            '$unwind': '$scouts.allotments.cookies'
        },
        {
            '$lookup': {
                'from': 'cookietypes',
                'localField': 'scouts.allotments.cookies.variety',
                'foreignField': 'name',
                'as': 'cookie'
            }
        },
        {
            '$unwind': '$cookie'
        },
        {
            '$project': {
                '_id': '$scouts._id',
                'firstname': '$scouts.firstname',
                'lastname': '$scouts.lastname',
                'totalvalue': {'$multiply': ['$scouts.allotments.cookies.quantity', '$cookie.price']}
            }
        },
        {
            '$group': {
                '_id': {'firstname': '$firstname', 'lastname': '$lastname'},
                'totalvalue': {'$sum': '$totalvalue'}
            }
        },
        {
            '$project': {
                'firstname': '$_id.firstname',
                'lastname': '$_id.lastname',
                'totalvalue': 1,
                '_id': 0
            }
        }
    ]
    sales_summary = list(troop.aggregate(pipeline))
    print(sales_summary)




def main_menu():
    """Displays the main menu and prompts the user for a choice."""
    while True:
        print("\nMain Menu")
        print("1. Troop Lookup")
        print("2. Scout Lookup")
        print("3. Sales Report")
        print("4. Quit")
        choice = input("Enter a choice: ")
        if choice == "1":
            troop_lookup()
        #elif choice == "2":
       #     scout_lookup()
        elif choice == "3":
            sales_report()
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main_menu()

