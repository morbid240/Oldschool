"""
Malcolm Roddy
CECS 323 
MongoDb homework
This code connects to database in atlas and has a 
user add delete and list data 
Due Date: 06/10/23
"""

from pymongo import MongoClient


class DepartmentManagementSystem:
    def __init__(self, collection):
        self.collection = collection

    def create_department(self, name, abbreviation, chair_name, building, office, description):
        if not self._is_department_exists(name):
            department = {
                "name": name,
                "abbreviation": abbreviation,
                "chair_name": chair_name,
                "building": building,
                "office": office,
                "description": description
            }
            self.collection.insert_one(department)
            print(f"Department '{name}' created successfully.")
        else:
            print(f"Department '{name}' already exists.")

    def list_departments(self):
        department_count = self.collection.estimated_document_count()
        if department_count == 0:
            print("No departments found.")
            return

        print(f"List of departments ({department_count}):")
        departments = self.collection.find().sort("name")
        for department in departments:
            print(department["name"])

    def delete_department(self, name):
        result = self.collection.delete_one({"name": name})
        if result.deleted_count == 1:
            print(f"Department '{name}' deleted successfully.")
            print("Number of departments deleted: 1")
        else:
            print(f"Department '{name}' does not exist.")

    def _is_department_exists(self, name):
        return self.collection.count_documents({"name": name}) > 0


def display_menu():
    print("Department Management System")
    print("1. Create a new department")
    print("2. List all departments")
    print("3. Delete a department")
    print("4. Exit")


def main(collection):
    dms = DepartmentManagementSystem(collection)

    while True:
        display_menu()
        choice = input("Enter your choice: ")

        if choice == "1":
            name = input("Enter department name: ")
            abbreviation = input("Enter department abbreviation: ")
            chair_name = input("Enter chair name: ")
            building = input("Enter building name: ")
            office = int(input("Enter office number: "))
            description = input("Enter department description: ")
            dms.create_department(name, abbreviation, chair_name, building, office, description)
        elif choice == "2":
            dms.list_departments()
        elif choice == "3":
            name = input("Enter department name to delete: ")
            dms.delete_department(name)
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    cluster = MongoClient("mongodb+srv://malcolmroddy01:Huckley1@cluster0.y1ujyrc.mongodb.net/?retryWrites=true&w=majority")
    db = cluster["SingleCollectionHW"]
    collection = db["Departments"]
    main(collection)