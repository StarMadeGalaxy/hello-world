from copy import deepcopy

flowers2 = ['rose', 'sunflower', 'jasmine']


def frag_make(flowers):
    fragrances = []
    fragrances.append([])   # без добавления пустого списка, мы не сможем сделать копию для вставки
    for flower in flowers:
        new_fragrance = deepcopy(fragrances)
        for fragrance in new_fragrance:
            fragrance.append(flower)
        fragrances += new_fragrance
    return fragrances


for i in frag_make(flowers2):
    print(i)