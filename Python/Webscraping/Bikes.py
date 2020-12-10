#------------------------------
# Bikes.py
# Author: Zach H
# Date: 09/16/2020
#
# Basic webscraper to find and
# record the name and price of
# all santa cruz brand Bikes
# with wheel size 27.5" and 29",
# Then record that info in a
# csv file
#------------------------------

from bs4 import BeautifulSoup as soup
from urllib.request import urlopen as uReq

page_url = "https://nexcess-production.santacruzbicycles.com/en-US/bikes"

uClient = uReq(page_url)
page_soup = soup(uClient.read(), "html.parser")
uClient.close()

# find all 27.5 and 29 inch wheel bike listings
# they are denoted by their picture (polaroid)
containers_1 = page_soup.findAll("div", {"class": "275quot polaroid"})
containers_2 = page_soup.findAll("div", {"class": "29quot polaroid"})

out_filename = "bikes.csv"
headers = "product_name,price \n"
f = open(out_filename, "w")
f.write(headers)

for container in containers_1:
    # in container find the h2 tag, then the a tag
    product_name = container.h2.a

    # in the table find table data, put it in an array
    temp = container.table.findAll("td", {"class": "polaroid__data"})
    price = temp[3]

    print("Product_Name: " + product_name.string + "\n")
    print("Price: " + price.string + "\n")

    # writes the dataset to file
    f.write(product_name.string + ", " + price.string.replace(",", "") + "\n")

for container in containers_2:

    product_name = container.h2.a

    temp = container.table.findAll("td", {"class": "polaroid__data"})
    price = temp[3]

    print("Product_Name: " + product_name.string + "\n")
    print("Price: " + price.string + "\n")

    f.write(product_name.string + ", " + price.string.replace(",", "") + "\n")

f.close()



