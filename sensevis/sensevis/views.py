from django.http import HttpResponse
from django.shortcuts import render

# Create your views here.
def index(request):
    context = {
        'indicator': 'Calorie',
        'date_range': '2022-01-01 to 2022-01-31',
    }

    return render(request, 'sensevis/index.html', context)
